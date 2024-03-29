#include <rmg/internal/context_load.hpp>

#include <utility>

#include <gtest/gtest.h>


using namespace rmg::internal;


class TestContextLoad: public ContextLoad {
  public:
    TestContextLoad() {}
    ~TestContextLoad() {}
    
    static int loadedCount;
    
    void load() override { loadedCount++; }
};

int TestContextLoad::loadedCount = 0;


/**
 * @brief Context loader pending instance constructor test
 */
TEST(ContextLoader_Pending, constructor) {
    ContextLoad *load1 = new TestContextLoad();
    
    Pending p1 = Pending();
    ASSERT_EQ(0, p1.getUseCount());
    
    Pending p2 = Pending(load1);
    ASSERT_EQ(1, p2.getUseCount());
    
    ContextLoad *load2 = new TestContextLoad();
    
    // Test if the reference count increases on copying
    Pending *p3 = new Pending(load2);
    ASSERT_EQ(1, p3->getUseCount()); // Reference count 1
    Pending p4 = *p3;
    ASSERT_EQ(2, p4.getUseCount()); // Reference count 1 to 2
    Pending p5;
    p5 = p4;
    ASSERT_EQ(3, p5.getUseCount()); // Reference count 2 to 3
    
    // Move constructor remains the reference count
    Pending p6 = std::move(p4);
    ASSERT_EQ(3, p6.getUseCount()); // Reference count still 3
    
    // Test if the reference count decreases on deletion
    delete p3;
    ASSERT_EQ(2, p5.getUseCount()); // Reference count 3 to 2
}




/**
 * @brief Context loader push test
 */
TEST(ContextLoader, push) {
    ContextLoad *load1 = new TestContextLoad();
    ContextLoad *load2 = new TestContextLoad();
    ContextLoad *load3 = new TestContextLoad();
    
    Pending p1 = Pending(load1);
    Pending p2 = Pending(load2);
    Pending p3 = p2;
    Pending p4 = Pending(load3);
    
    // Load count increases each time a load is pushed
    ContextLoader loader;
    ASSERT_EQ(0, loader.getLoadCount()); // Load count 0
    loader.push(p1);
    ASSERT_EQ(1, loader.getLoadCount()); // Load count 0 to 1
    loader.push(p2);
    ASSERT_EQ(2, loader.getLoadCount()); // Load count 1 to 2
    
    /**
     * The load count should not increase since p2 and p3 are pointed to
     * duplicated load instance.
     */
    loader.push(p3);
    ASSERT_EQ(2, loader.getLoadCount()); // Load count still 2
    
    // Pushing load with null pointers should be rejected
    loader.push(Pending());
    ASSERT_EQ(2, loader.getLoadCount()); // Load count still 2
    
    // Pushing still works normally
    loader.push(p4);
    ASSERT_EQ(3, loader.getLoadCount()); // Load count 2 to 3
}




/**
 * @brief Context loader load test
 */
TEST(ContextLoader, load) {
    ContextLoad *load1 = new TestContextLoad();
    ContextLoad *load2 = new TestContextLoad();
    ContextLoad *load3 = new TestContextLoad();
    ContextLoad *load4 = new TestContextLoad();
    
    Pending p1 = Pending(load1);
    Pending p2 = Pending(load2);
    Pending p3 = Pending(load3);
    Pending *p4 = new Pending(load4);
    
    int count = TestContextLoad::loadedCount;
    ContextLoader loader;
    
    loader.push(p1);
    loader.push(p2);
    ASSERT_EQ(2, loader.getLoadCount());
    loader.load();
    ASSERT_EQ(0, loader.getLoadCount());
    
    // The assertion indicates that 2 new loads have been receantly loaded.
    ASSERT_EQ(count+2, TestContextLoad::loadedCount);
    
    
    loader.push(p3);
    loader.push(*p4);
    delete p4;
    ASSERT_EQ(2, loader.getLoadCount());
    loader.load();
    
    // Only load3 should be loaded since reference count to load4 is zero
    ASSERT_EQ(count+3, TestContextLoad::loadedCount);
}

TEST(ContextLoader, load_empty) {
    ASSERT_EXIT(
        {
            Pending empty;
            ContextLoader loader;
            loader.push(empty);
            loader.load();
            exit(0);
        },
        ::testing::ExitedWithCode(0),
        ".*"
    );
}
