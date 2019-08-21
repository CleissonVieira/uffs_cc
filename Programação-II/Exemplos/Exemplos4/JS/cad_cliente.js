    document.getElementById("perfilP").onclick = function(){
    document.getElementById("empresa").disabled = false;
    document.getElementById("mensagem-empresa").innerHTML = "Entre em contato para estabelecer uma parceria!";
    //innerHTML para modificar ou escrever conteúdo de texto
};

document.getElementById("perfilC").onclick = function(){
    document.getElementById("empresa").value = "";
    document.getElementById("mensagem-empresa").innerHTML = "";
    document.getElementById("empresa").disabled = true;
};


document.getElementById("form-contato").onsubmit = validaCadastro;
document.getElementById("form-contato").onsubmit = preencherCpf;

function validaCadastro(){
    var contErro = 0;
    var nome = document.getElementById("nome");
    var erro_nome = document.getElementById("msg-nome");
    if((nome.value == "") || (nome.value.indexOf(" ") == -1)){
        erro_nome.innerHTML = "Por favor digite o Nome completo."
        erro_nome.display = "block";
        contErro += 1;
    }else{
        erro_nome.display = "none";
    }
    if(contErro > 0)
        return false;
    else
        alert("Cadastro efetuado com sucesso!"); //será removido posteriormente

    return false;
}

function preencherCpf(){
    var cpf = document.querySelector("#cpf");
    cpf.addEventListener("blur", function(){
        cpf.value = cpf.value.match(/.{1,3}/g).join(".").replace(/\.(?=[^.]*$)/,"-");
    });
}

var cpf = document.querySelector("#cpf");

cpf.addEventListener("blur", function(){
   cpf.value = cpf.value.match(/.{1,3}/g).join(".").replace(/\.(?=[^.]*$)/,"-");
});