#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>

//Programa feito com a IDE Code::Blocks

    //declara as vari�veis globais, que s�o acessiveis em todas as fun��es do programa
    GtkBuilder *builder;
    GtkWidget *window;
    GtkStack *stack;
    GtkListStore *bancoDados;
    GtkListStore *dadosClass;

    //Declara os itens que estar�o no banco de dados
    typedef struct naves
    {
        int id;
        char tamanho[100];
        char cor[100];
        char local[100];
        int codPoder;
        char textPoder[100];
        char tpArm[100];
        char tpComb[100];
        int nTrip;
        char estTrip[100];
        int codAvaria;
        char textAvaria[100];
        int potencial;
        int codPerigo;
        char textPerigo[100];
        struct naves *proximo;
    }nave;
    //Aplica valor � variavel id
    int id = 0;
    //Declara as variaveis referentes � base de dados
    nave *headerNave;
    nave *proxNave;

    //Declara os itens que estar�o na classifica��o
    typedef struct classList
    {
        int id;
        int codPoder;
        int codAvaria;
        int potencial;
        int codPerigo;
        char classificacao[100];
        struct classList *proximoClass;
    } classNaves;
    //Declara as variaveis referentes � base de classifica��o
    classNaves *headerClass;
    classNaves *proxClass;

    //Fun��o para fechar o programa
    void on_mainWindow_destroy(GtkWidget *widget, gpointer data)
    {
        gtk_main_quit();
    }

    //BLOCO DE LOGIN
    //Fun��o para exibir a mensagem de erro ou sucesso na tela
    void mensagem(char texto[100], char secTexto[100], char nomeIcon[100])
    {
        //Declara a variavel mensagem e linka ela com o builder
        GtkWidget *mensagem = GTK_WIDGET(gtk_builder_get_object(builder, "mensagem"));

        //define os parametros da mensagem a ser exibida
        g_object_set(mensagem, "text", texto, NULL);
        g_object_set(mensagem, "secondary_text", secTexto, NULL);
        g_object_set(mensagem, "icon_name", nomeIcon, NULL);

        //Exibe a janela de mensagem e aguarda resposta
        gtk_widget_show_all(mensagem);//Exibe a janela de mensagem e aguarda resposta
        gtk_dialog_run(GTK_DIALOG(mensagem));//Cast para GtkDialo
        gtk_widget_hide(mensagem);//Esconde a janela ap�s o fechamento

    }
    //Fun��o para fazer login no programa
    void login(char *user, char *senha)
    {
        //Se o usu�rio e a senha inseridos estiverem corretos, abre a tela da home da interface
        if((strcmp(user,"Coder")==0) && (strcmp(senha,"123456")==0))
        {
            gtk_stack_set_visible_child_name(stack, "homeWindow");
        }
        //Se o usu�rio e a senha inseridos estiverem incorretos, chama uma mensagem de erro
        else if((strcmp(user,"Coder")!=0)&&(strcmp(senha,"123456")!=0))
        {
            mensagem("Falha no Login", "Usuario e Senha incorretos.","dialog-error");

        }
        //Se a senha inserida estiver incorreta, chama uma mensagem de erro
        else if((strcmp(senha,"123456")!=0))
        {

            mensagem("Falha no Login", "Senha incorreta","dialog-error");
        }
        //Sen�o, o usuario inserido estara incorreto, chamamando uma mensagem de erro
        else
        {
            mensagem("Falha no Login", "Usuario incorreto","dialog-error");
        }
    }
    //Fun��o que guarda o usuario e senha da interface e passa pra fun��o que faz o login
    void on_btnlogin_clicked(GtkWidget *widget, gpointer data)
    {
        //Importa o valor inserido da interface
        GtkEntry *entry_user = GTK_ENTRY(gtk_builder_get_object(builder, "logUser"));
        GtkEntry *entry_senha = GTK_ENTRY(gtk_builder_get_object(builder, "logSenha"));

        //Cria uma variavel no codigo com o valor importado da interface
        char *user = gtk_entry_get_text(entry_user);
        char *senha = gtk_entry_get_text(entry_senha);
        //passa as informa��es para a fun��o login
        login(user, senha);
    }

    //BLOCO DA HOME
    //Fun��o para abrir a tela de cadastro de naves
    void on_btnCadastro_clicked(GtkWidget *widget, gpointer data)
    {
        gtk_stack_set_visible_child_name(stack, "cadastroWindow");
    }
    //Fun��o para abrir a tela de consulta de naves cadastradas
    void on_btnConsulta_clicked(GtkWidget *widget, gpointer data)
    {
        gtk_stack_set_visible_child_name(stack, "consultaWindow");
    }
    //Fun��o para abrir a tela de classifica��o de naves
    void on_btnClassificacao_clicked(GtkWidget *widget, gpointer data)
    {
        gtk_stack_set_visible_child_name(stack, "classificacaoWindow");
    }
    //Fun��o para voltar pra tela de login
    void on_btnSair_clicked(GtkWidget *widget, gpointer data)
    {
        gtk_stack_set_visible_child_name(stack, "loginWindow");
        //Quando o programa sai de uma tela maior e migra pra uma menor, � preciso redimensionar a tela ao tamanho antigo
        gtk_window_resize(GTK_WINDOW(window), 350, 300);
    }

    //BLOCO DE CADASTRO
    //Fun��o para voltar pra tela da home
    void on_btnCadVoltar_clicked(GtkWidget *widget, gpointer data)
    {
        gtk_stack_set_visible_child_name(stack, "homeWindow");
        //Quando o programa sai de uma tela maior e migra pra uma menor, � preciso redimensionar a tela ao tamanho antigo
        gtk_window_resize(GTK_WINDOW(window), 800, 600);
    }

    //Fun��o para cadastrar os itens na base de dados
    void on_btnCadastrar_clicked(GtkWidget *widget, gpointer data)
    {
        //Importa os valores inseridos na interface
        GtkEntry *entry_tamanho = GTK_ENTRY(gtk_builder_get_object(builder, "cadTamanho"));
        GtkEntry *entry_cor = GTK_ENTRY(gtk_builder_get_object(builder, "cadCor"));
        GtkEntry *entry_local = GTK_ENTRY(gtk_builder_get_object(builder, "cadLocal"));
        GtkEntry *entry_poder = GTK_ENTRY(gtk_builder_get_object(builder, "cadPoderio"));
        GtkEntry *entry_tipoArmas = GTK_ENTRY(gtk_builder_get_object(builder, "cadTipoArmas"));
        GtkEntry *entry_tipoComb = GTK_ENTRY(gtk_builder_get_object(builder, "cadTipoCombustivel"));
        GtkEntry *entry_nTrip = GTK_ENTRY(gtk_builder_get_object(builder, "cadNumTripulantes"));
        GtkEntry *entry_estado = GTK_ENTRY(gtk_builder_get_object(builder, "cadEstadoTripulantes"));
        GtkEntry *entry_codAvaria = GTK_ENTRY(gtk_builder_get_object(builder, "cadGrauAvaria"));
        GtkEntry *entry_potencial = GTK_ENTRY(gtk_builder_get_object(builder, "cadPotencial"));
        GtkEntry *entry_perigo = GTK_ENTRY(gtk_builder_get_object(builder, "cadPericulosidade"));

        //Cria uma variavel no codigo com os valor importados da interface
        char *cadTamanho = gtk_entry_get_text(entry_tamanho);
        char *cadCor = gtk_entry_get_text(entry_cor);
        char *cadLocal = gtk_entry_get_text(entry_local);
        char *cadTipoArm = gtk_entry_get_text(entry_tipoArmas);
        char *cadTipoComb = gtk_entry_get_text(entry_tipoComb);
        char *cadEstTrip = gtk_entry_get_text(entry_estado);

        //Variavel usada na convers�o de string para int
        char*endptr;
        //Converte o tipo de valor de string para int
        int cadPoder = (int) strtol(gtk_entry_get_text(entry_poder), &endptr, 10);
        if (*endptr != '\0')
        {   //Significa que a convers�o falhou (n�o era um n�mero v�lido)
            mensagem("Caracteres invalidos", "Voce digitou texto em um campo numerico.","dialog-error");
            return;
        }
        int cadNumTrp = (int) strtol(gtk_entry_get_text(entry_nTrip), &endptr, 10);
        if (*endptr != '\0')
        {   // Significa que a convers�o falhou (n�o era um n�mero v�lido)
            mensagem("Caracteres invalidos", "Voce digitou texto em um campo numerico.","dialog-error");
            return;
        }
        int cadCodAvaria = (int) strtol(gtk_entry_get_text(entry_codAvaria), &endptr, 10);
        if (*endptr != '\0')
        {   // Significa que a convers�o falhou (n�o era um n�mero v�lido)
            mensagem("Caracteres invalidos", "Voce digitou texto em um campo numerico.","dialog-error");
            return;
        }
        int cadPotencial = (int) strtol(gtk_entry_get_text(entry_potencial), &endptr, 10);
        if (*endptr != '\0')
        {   // Significa que a convers�o falhou (n�o era um n�mero v�lido)
            mensagem("Caracteres invalidos", "Voce digitou texto em um campo numerico.","dialog-error");
            return;
        }
        int cadPerigo = (int) strtol(gtk_entry_get_text(entry_perigo), &endptr, 10);
        if (*endptr != '\0')
        {   // Significa que a convers�o falhou (n�o era um n�mero v�lido)
            mensagem("Caracteres invalidos", "Voce digitou texto em um campo numerico.","dialog-error");
            return;
        }

        //Se existir algum valor vazio, pede para o usuario preencher tudo. Sen�o, passa pra proxima verifica��o
        if((strcmp(cadTamanho,"")==0)||(strcmp(cadCor,"")==0)||(strcmp(cadLocal,"")==0)||(strcmp(gtk_entry_get_text(entry_poder),"")==0)||(strcmp(cadTipoArm,"")==0)||(strcmp(cadTipoComb,"")==0)||
        (strcmp(gtk_entry_get_text(entry_nTrip),"")==0)||(strcmp(cadEstTrip,"")==0)||(strcmp(gtk_entry_get_text(entry_codAvaria),"")==0)||(strcmp(gtk_entry_get_text(entry_potencial),"")==0)||(strcmp(gtk_entry_get_text(entry_perigo),"")==0))
        {
            mensagem("Campos Vazios", "Voce deixou campos vazios.","dialog-error");
        }
        //Se todos os valores numericos estiverem nos padr�es corretos, efetua o cadastro
        else if((cadPoder >= 0 && cadPoder < 5)&&(cadNumTrp >= 0 && cadNumTrp <= 100000)&&(cadCodAvaria >= 0 && cadCodAvaria < 5)&&
        (cadPotencial >= 0 && cadPotencial < 5)&&(cadPerigo >= 0 && cadPerigo < 5))
        {
            //Comandos para efetuar o cadastro
            id++;
            proxNave -> id = id;
            strcpy(proxNave->tamanho, cadTamanho);
            strcpy(proxNave->cor, cadCor);
            strcpy(proxNave->local, cadLocal);
            proxNave -> codPoder = cadPoder;
            //Com base no valor num�rico digitado, printa um texto diferente
            switch (cadPoder)
            {
                case 0:
                    strcpy(proxNave->textPoder, "Inexistente");
                    break;
                case 1:
                    strcpy(proxNave->textPoder, "Baixissimo");
                    break;
                case 2:
                    strcpy(proxNave->textPoder, "Intermediario");
                    break;
                case 3:
                    strcpy(proxNave->textPoder, "Potente");
                    break;
                case 4:
                    strcpy(proxNave->textPoder, "Mais de oito Mil");
                    break;
            }
            strcpy(proxNave->tpArm, cadTipoArm);
            strcpy(proxNave->tpComb, cadTipoComb);
            proxNave -> nTrip = cadNumTrp;
            strcpy(proxNave->estTrip, cadEstTrip);
            proxNave -> codAvaria = cadCodAvaria;
            //Com base no valor num�rico digitado, printa um texto diferente
            switch (cadCodAvaria)
            {
                case 0:
                    strcpy(proxNave->textAvaria, "Perfeita");
                    break;
                case 1:
                    strcpy(proxNave->textAvaria, "Arranhada");
                    break;
                case 2:
                    strcpy(proxNave->textAvaria, "Danificada");
                    break;
                case 3:
                    strcpy(proxNave->textAvaria, "Estourada");
                    break;
                case 4:
                    strcpy(proxNave->textAvaria, "Inutilizavel");
                    break;
            }
            proxNave -> potencial = cadPotencial;
            proxNave -> codPerigo = cadPerigo;
            //Com base no valor num�rico digitado, printa um texto diferente
            switch (cadPerigo)
            {
                case 0:
                    strcpy(proxNave->textPerigo, "Inofensiva");
                    break;
                case 1:
                    strcpy(proxNave->textPerigo, "Levemente Perigosa");
                    break;
                case 2:
                    strcpy(proxNave->textPerigo, "Perigosa");
                    break;
                case 3:
                    strcpy(proxNave->textPerigo, "Calamidade");
                    break;
                case 4:
                    strcpy(proxNave->textPerigo, "Extingue a humanidade");
                    break;
            }

            // Adiciona tambem os valores para classifica��o em uma outra lista
            proxClass -> id = id;
            proxClass -> codPoder = cadPoder;
            proxClass -> codAvaria = cadCodAvaria;
            proxClass -> potencial = cadPotencial;
            proxClass -> codPerigo = cadPerigo;

            //Exibe a mensagem de cadastro concluido
            mensagem("Cadastro Concluido", "A linha foi cadastrada com sucesso.","emblem-default");

            //Atualiza o tamanho da memoria usada para guardar os itens cadastrados e classificados
            proxNave->proximo = (nave *)malloc(sizeof(nave));
            proxNave = proxNave->proximo;
            proxClass->proximoClass = (classNaves *)malloc(sizeof(classNaves));
            proxClass = proxClass->proximoClass;
        }
        //Caso contrario, retorna erro
        else
        {
            //Mensagem de erro
            mensagem("Numeros fora dos parametros", "Os numeros precisam estar entre 0 e 4.","dialog-error");
        }
    }

    //BLOCO DE LISTAGEM DE ITENS
    //Fun��o para voltar pra tela da home
    void on_btnListVoltar_clicked(GtkWidget *widget, gpointer data)
    {
        gtk_stack_set_visible_child_name(stack, "homeWindow");
        //Quando o programa sai de uma tela maior e migra pra uma menor, � preciso redimensionar a tela ao tamanho antigo
        gtk_window_resize(GTK_WINDOW(window), 800, 600);
    }

    //Fun��o para listar as naves cadastradas
    void on_btnListar_clicked(GtkWidget *widget, gpointer data)
    {
        //variavel necessaria para cadastrar os itens na liststore
        GtkTreeIter iter;
        //Limpa o store da tabela de classifica��o antes de exibir novos valores
        gtk_list_store_clear(bancoDados);

        //Anula o valor do proximo valor a ser digitado, pois n�o sera acrescentado mais nada durante a execu��o desse trecho
        proxNave->proximo = NULL;
        proxNave = headerNave;

        //Enquanto o proximo valor n�o for nulo (que seria o ultimo), printa a linha na tela.
        while(proxNave->proximo != NULL)
        {
            //Adiciona uma nova linha ao banco de dados
            gtk_list_store_append(bancoDados, &iter);
            //Adiciona os valores as suas respectivas colunas
            gtk_list_store_set(bancoDados, &iter,
                                0, proxNave -> id,
                                1, proxNave->tamanho,
                                2, proxNave->cor,
                                3, proxNave->local,
                                4, proxNave -> codPoder,
                                5, proxNave->textPoder,
                                6, proxNave->tpArm,
                                7, proxNave->tpComb,
                                8, proxNave->nTrip,
                                9, proxNave->estTrip,
                                10, proxNave -> codAvaria,
                                11, proxNave->textAvaria,
                                12, proxNave -> potencial,
                                13, proxNave -> codPerigo,
                                14, proxNave->textPerigo,
                                -1);
            //Passa para a proxima linha a ser registrada
            proxNave = proxNave->proximo;
        }
    }

    //BLOCO DE CLASIFICA��O DE ITENS
    //Fun��o para voltar pra tela da home
    void on_btnClassVoltar_clicked()
    {
        gtk_stack_set_visible_child_name(stack, "homeWindow");
        //Quando o programa sai de uma tela maior e migra pra uma menor, � preciso redimensionar a tela ao tamanho antigo
        gtk_window_resize(GTK_WINDOW(window), 800, 600);
    }
    //Fun��o para classificar e listar as naves
    void on_btnClassificar_clicked(GtkWidget *widget, gpointer data)
    {
        //variavel necessaria para cadastrar os itens na liststore
        GtkTreeIter iter;
        //Limpa o store da tabela de classifica��o antes de exibir novos valores
        gtk_list_store_clear(dadosClass);

        //Anula o valor do proximo valor a ser digitado, pois n�o sera acrescentado mais nada durante a execu��o desse trecho
        proxClass->proximoClass = NULL;
        proxClass = headerClass;

        //Enquanto o proximo valor n�o for nulo (que seria o ultimo), printa a linha na tela.
        while(proxClass->proximoClass != NULL)
        {
            //Adiciona uma nova linha ao banco de dados
            gtk_list_store_append(dadosClass, &iter);

            //CLASSIFICA��O DAS NAVES
            //Variaveis usadas para classificar as naves
            int pow= proxClass -> codPoder, av= proxClass -> codAvaria, pot= proxClass -> potencial, per=proxClass -> codPerigo;

            //Se o grau de avaria for elevado e nenhum dos outros campos for maior que zero, Descartar nave
            if (av>2 && pow==0 && pot==0 && per==0)
                strcpy(proxClass -> classificacao, "Sucata Espacial");
            //Se o grau de avaria for entre 1 e 2 e os outros campos conterem valores baixos, considerar reparar
            else if ((av==1 || av==2) && per<3 && (pot>0 && pot<3) && pow<3)
                strcpy(proxClass -> classificacao, "Cogitar Reparo");
            //Se o grau de avaria for baixo, o potencial tecnologico for baixo e a periculosidade e poder belico inexistentes, utilizar no cotidiano para fun��es especificas
             else if (av<3 && per==0 && pow==0 && pot<2)
                strcpy(proxClass -> classificacao, "Uso Comum");
            //Se o potencial tecnologico for maior que 2, o poder belico e a periculosidade menor que 3, � uma j�ia tecnologica
            else if (av<5 && per<3 && pow<3 && pot>2)
                strcpy(proxClass -> classificacao, "Joia Tecnologica");
            //Se o poder belico for maior que zero e menor que 4 e o potencial, periculosidade e avaria menores que 3, vai pro arsenal militar
            else if (av<3 && per<3 && (pow>0 && pow<4) && pot<3)
                strcpy(proxClass -> classificacao, "Arsenal Militar");
            //Se a periculosidade for igual a 3 e o poder belico menor que 4, vai pra area 51
            else if (av<5 && per==3 && pow<4 && pot<5)
                strcpy(proxClass -> classificacao, "Vai pra Area 51");
            //Se a periculosidade for igual a 4, � uma amea�a a vida humana
            else if (av<5 && per==4 && pow<5 && pot<5)
                strcpy(proxClass -> classificacao, "Ameaca a Humanidade");
            //Caso n�o seja nada disso, � uma cobaia cientifica
            else
                strcpy(proxClass -> classificacao, "Cobaia Cientifica");

            //RETOMA O CADASTRO DOS ITENS
            //Adiciona os valores as suas respectivas colunas
            gtk_list_store_set(dadosClass, &iter,
                               0, proxClass -> id,
                               1, proxClass -> codPoder,
                               2, proxClass -> codAvaria,
                               3, proxClass -> potencial,
                               4, proxClass -> codPerigo,
                               5, proxClass -> classificacao,
                               -1);

            //Passa para a proxima linha a ser registrada
            proxClass = proxClass->proximoClass;
        }
    }

    //MAIN
    //Fun��o principal, onde ser�o carregadas as demais fun��es, arquivos auxiliares, callbacks e a interface
    int main(int argc, char *argv[])
    {
        // Inicializa o GTK
        gtk_init(&argc, &argv);

        //Importa o arquivo glade ao c�digo
        builder = gtk_builder_new_from_file("UI.glade");

        //Adiciona os callbacks ao builder
        gtk_builder_add_callback_symbol(builder,"on_mainWindow_destroy",G_CALLBACK(on_mainWindow_destroy));
        gtk_builder_add_callback_symbol(builder,"on_btnlogin_clicked",G_CALLBACK(on_btnlogin_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnCadastro_clicked",G_CALLBACK(on_btnCadastro_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnConsulta_clicked",G_CALLBACK(on_btnConsulta_clicked));
        gtk_builder_add_callback_symbol(builder,"on_mainWindow_destroy",G_CALLBACK(on_mainWindow_destroy));
        gtk_builder_add_callback_symbol(builder,"on_btnlogin_clicked",G_CALLBACK(on_btnlogin_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnCadastro_clicked",G_CALLBACK(on_btnCadastro_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnConsulta_clicked",G_CALLBACK(on_btnConsulta_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnClassificacao_clicked",G_CALLBACK(on_btnClassificacao_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnSair_clicked",G_CALLBACK(on_btnSair_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnCadVoltar_clicked",G_CALLBACK(on_btnCadVoltar_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnCadastrar_clicked",G_CALLBACK(on_btnCadastrar_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnListVoltar_clicked",G_CALLBACK(on_btnListVoltar_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnListar_clicked",G_CALLBACK(on_btnListar_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnClassVoltar_clicked",G_CALLBACK(on_btnClassVoltar_clicked));
        gtk_builder_add_callback_symbol(builder,"on_btnClassificar_clicked",  G_CALLBACK(on_btnClassificar_clicked));
        //Conecta o builder com os sinais do glade
        gtk_builder_connect_signals(builder, NULL);

        //Inicia as variaveis que ser�o utilizadas no c�digo
        window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
        stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
        bancoDados = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
        dadosClass = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore2"));
        //Aloca espa�o na mem�ria para as variaveis
        headerNave = (nave *)malloc(sizeof(nave));
        headerClass = (classNaves *)malloc(sizeof(classNaves));
        //Inicia as variaveis que ser�o utilizadas no c�digo
        proxClass = headerClass;
        proxNave = headerNave;

        // Mostra a janela
        gtk_widget_show_all(window);
        // Inicia o loop principal do GTK
        gtk_main();
        return 0;
    }
