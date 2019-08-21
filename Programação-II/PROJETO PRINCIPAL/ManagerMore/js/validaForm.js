/*o parâmetro frm das funções significa: this.form,
pois a chamada da função - validaForm(this) foi
definida na tag form.*/

function validaCadastro(frm) {
    //Verifica se o campo nome foi preenchido
    if(frm.nome.value == "" || frm.nome.value == null) {
        alert("Indique o nome da sua empresa.");
        return false;
    }
    //Verifica se o campo CNJP Matriz foi preenchido
    if(frm.cnpj_matriz.value == "" || frm.cnpj_matriz.value == null) {
        alert("Indique o CNPJ Matriz da sua empresa.");
        return false;
    }
    //Verifica se o campo nome foi preenchido
    if(frm.senha.value == "" || frm.senha.value == null) {
        alert("Insira sua senha.");
        return false;
    }
    //Verifica se o campo confirma senha é igual ao campo senha
    if(frm.senha.value != frm.confirm_senha.value) {
        alert("As senhas não correspondem.");
        return false;
    }
    //Verifica se o campo inscrição estadual foi preenchido
    if(frm.insc_estadual.value == "" || frm.insc_estadual.value == null) {
        alert("Insira a Inscrição Estadual da sua empresa..");
        return false;
    }
    //o campo e-mail precisa de conter: "@", "." e não pode estar vazio
    if(frm.email.value.indexOf("@") == -1 || frm.email.value.indexOf(".") == -1) {
        alert("Por favor, indique um e-mail válido.");
        frm.email.focus();
        return false;
    }
    //Verifica se o campo telefone foi preenchido
    if(frm.telefone.value == "" || frm.telefone.value == null) {
        alert("Insira um número de telefone.");
        return false;
    }
    //Verifica se o campo endereço foi preenchido
    if(frm.endereco.value == "" || frm.endereco.value == null) {
        alert("Insira o endereço da matriz da sua empresa.");
        return false;
    }
    //Verifica se o campo de cocordar com os termos está selecionado
    if(frm.termos.checked == false) {
        alert("É necessário concordar com os termos de serviço.");
        return false;
    }
}

function validaLogin(frm) {
    //Verifica se o campo nome foi preenchido e
    if(frm.nome.value == "" || frm.nome.value == null) {
        alert("Por favor, indique o seu nome.");
        return false;
    }
    //Verifica se o campo senha foi preenchido e
    if(frm.senha.value == "" || frm.senha.value == null) {
        alert("Por favor, insira sua senha.");
        return false;
    }
        
}

function validaEmail(frm) {
    //o campo e-mail precisa de conter: "@", "." e não pode estar vazio
    if(frm.email.value.indexOf("@") == -1 || frm.email.value.indexOf(".") == -1) {
        alert("Por favor, indique um e-mail válido.");
        frm.email.focus();
        return false;
    }
}