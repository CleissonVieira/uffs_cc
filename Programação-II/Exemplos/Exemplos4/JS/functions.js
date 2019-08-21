
document.getElementById("fechar").onclick = function(){	
	document.getElementById("ajuda").style.display = 'none';
};

document.getElementById("exibeMenu").onclick = function(){
	var menu = document.getElementsByClassName("menu-opcoes")[0];
	if(menu.style.display == 'block')
		menu.style.display = 'none';
	else
		menu.style.display = 'block';
};

document.body.onresize = function(){
    var w = window.outerWidth;
    var menu = document.getElementsByClassName("menu-opcoes")[0];
    if (w >= 1000){
		menu.style.display = 'block';
    } else{
		menu.style.display = 'none';    	
    }
};

