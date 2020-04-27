var projectname_txt, projectbrief_txt;

window.addEventListener("load", function() {
    projectname_txt = document.getElementById("projectname");
    projectbrief_txt = document.getElementById("projectbrief");
    
    if(window.innerWidth < 700) {
        projectname_txt.innerHTML = "RMGraphics";
        projectbrief_txt.style.display = "none";
    }
    if(window.innerWidth < 800) {
        $("#doc-content").css({marginLeft:6+"px"});
        $("#side-nav").css({width:0 + "px"});
    }
    var handle = document.getElementsByClassName("ui-resizable-handle");
    for(let i=0; i<handle.length; i++) {
        var new_element = handle[i].cloneNode(true);
        handle[i].parentNode.replaceChild(new_element, handle[i]);
    }
});

window.addEventListener("resize", function() {
    if(window.innerWidth < 700) {
        projectname_txt.innerHTML = "RMGraphics";
        projectbrief_txt.style.display = "none";
    }
    else {
        projectname_txt.innerHTML = "Robot Monitor Graphics";
        projectbrief_txt.style.display = "block";
    }
});
