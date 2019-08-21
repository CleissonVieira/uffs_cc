document.getElementById("form-cadastro").onsubmit = function(){
    var contErro = 0;
    var nome = document.getElementById("nome");
    var erro_nome = document.getElementById("msg-nome");
    if(nome.value == ""){
        erro_nome.innerHTML = "Por favor digite seu Nome."
        erro_nome.display = "block";
        contErro += 1;
    }else{
        erro_nome.display = "none";
    }
    if(contErro > 0)
        return false;
    else
        alert("Cadastro efetuado com sucesso!");
    return false;
}