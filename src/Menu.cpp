#include "Menu.h"
#include "DataManager.h"


#include <iostream>


Menu::Menu(DataManager& management) : management_(management) {

}


void Menu::setManagement(const DataManager &management) {
    management_ = management;
}

string to_lower (string str)
{
    for(auto& elem : str)
    {elem = tolower(elem);}
    return str;
}


void Menu::start() {
    management_.readStudentClasses();
    management_.readClasses();
    int choice;
    do {
        // Menu Principal
        cout << "╔═════════════════════════════════╗" << endl;
        cout << "║          Menu Principal         ║" << endl;
        cout << "║                                 ║" << endl;
        cout << "║ 1. Consultar horários           ║" << endl;
        cout << "║ 2. Consultar dados de alunos    ║" << endl;
        cout << "║ 3. Consultar dados de UCs       ║" << endl;
        cout << "║    e turmas                     ║" << endl;
        cout << "║ 4. Realizar pedido de alteração ║" << endl;
        cout << "║ 5. Histórico de Pedidos         ║" << endl;
        cout << "║    Pendentes                    ║" << endl;
        cout << "║ 6. Processar pedidos            ║" << endl;
        cout << "║ 7. Sair do programa             ║" << endl;
        cout << "║                                 ║" << endl;
        cout << "╚═════════════════════════════════╝" << endl;
        cout << "Por favor, escolha uma opção (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                consultarHorarios();
                break;
            case 2:
                consultarInformacoesAlunos();
                break;
            case 3:
                consultarTurmaAnoCursoUC();
                break;
            case 4:
                realizarAlteracoes();
                break;
            case 5:
                visualizarHistoricoPedidos();
                break;
            case 6:
                processarPedidos();
                break;
            case 7:
                cout << "A sair do programa." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-5)." << endl;
                break;
        }
    } while (choice != 5);
}

void Menu::consultarHorarios() {
    int choice;
    do {
        // Menu da Página de Consulta de Horários
        cout << "╔══════════════════════════════════╗" << endl;
        cout << "║  Página de Consulta de Horários  ║" << endl;
        cout << "║                                  ║" << endl;
        cout << "║ 1. Consultar horário de aluno    ║" << endl;
        cout << "║ 2. Consultar horário de turma    ║" << endl;
        cout << "║ 3. Consultar horário de UC       ║" << endl;
        cout << "║ 4. Consultar horário de UC/turma ║" << endl;
        cout << "║ 5. Voltar ao menu principal      ║" << endl;
        cout << "║                                  ║" << endl;
        cout << "╚══════════════════════════════════╝" << endl;
        cout << "Por favor, escolha uma opção (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                consultarHorarioAluno();
                break;
            case 2:
                consultarHorarioTurma();
                break;
            case 3:
                consultarHorarioUC();
                break;
            case 4:
                consultarHorarioUCTurma();
                break;
            case 5:
                cout << "A voltar ao menu principal." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-5)." << endl;
                break;
        }
    } while (choice != 5);
}




//consultar o horário de um aluno
void Menu::consultarHorarioAluno() {
    string id;
    cout << "--------------------------------------------------\n";
    cout << "Introduza o nome do estudante ou número UP:";
    cin >> id;
    cout << endl;
    bool isValid = false;

    for (const Student& stu : management_.getStudents()) {
        if (std::to_string(stu.getCode()) == id || to_lower(stu.getName()) == to_lower(id)) {
            isValid = true;
            cout << "O estudante " << stu.getName() << " (" << stu.getCode()
                 << ") tem o seguinte horário:\n" << endl;

            vector<ClassUC> listC = stu.getclassUC();

            for (const ClassUC& turmaAluno : listC) {
                cout << turmaAluno.getUcCode() << " -- " << turmaAluno.getClassCode() << endl;

                for (const Slot& horario : turmaAluno.getSchedule()) {
                    cout << '\t' << horario.getDay() << ' ' << horario.getStart() << ' ' << horario.getDuration() << ' ' << horario.getType() << '\n';
                }
            }
            cout << endl;
        }
    }

    if (!isValid) {
        cout << "Nome/número de estudante inválido.\n";
    }
}


//consultar o horário de um aluno




//consultar o horário de uma turma
void Menu::consultarHorarioTurma() {
    string classCode;
    cout << "--------------------------------------------------\n";
    cout << "Por favor, insira o código da turma: ";
    cin >> classCode;
    cout << endl;

    bool isValid = false;
    const vector<ClassUC>& allUCs = management_.getAllUC();

    for (const ClassUC& uc : allUCs) {
        if (isClassCodeValid(classCode, uc.getClassCode())) {
            isValid = true;
            displayClassSchedule(uc);
        }
    }

    if (!isValid) {
        cout << "That's not a valid input." << endl;
    }
}

bool Menu::isClassCodeValid(const string& input, const string& target) const {
    return to_lower(input) == to_lower(target);
}

void Menu::displayClassSchedule(const ClassUC& uc) const {
    cout << uc.getUcCode() << endl;

    for (const Slot& a : uc.getSchedule()) {
        cout << '\t' << a.getDay() << ' ' << a.getStart() << ' ' << a.getDuration() << ' ' << a.getType() << '\n';
    }
}
//consultar o horário de uma turma



//consultar o horário de uma UC
void Menu::consultarHorarioUC() {
    string ucCode;

    cout << "--------------------------------------------------\n";
    cout << "Digite o Código da UC: ";
    cin >> ucCode;
    cout << endl;

    const vector<ClassUC>& todasAsTurmas = management_.getAllUC();
    bool encontrouUC = false;

    for (const ClassUC& turma : todasAsTurmas) {
        if (correspondeCodigoUC(turma, ucCode)) {
            encontrouUC = true;
            exibirHorarioDaUC(turma);
        }
    }

    if (!encontrouUC) {
        cout << "Código de UC inválido." << endl;
    }
}

bool Menu::correspondeCodigoUC(const ClassUC& turma, const string& ucCode) const {
    return compararIgnorandoMaiusculas(turma.getUcCode(), ucCode);
}

void Menu::exibirHorarioDaUC(const ClassUC& turma) const {
    cout << turma.getClassCode() << endl;
    for (const Slot& horario : turma.getSchedule()) {
        cout << '\t' << horario.getDay() << ' ' << horario.getStart() << ' ' << horario.getDuration() << ' ' << horario.getType() << '\n';
    }
}

bool Menu::compararIgnorandoMaiusculas(const string& str1, const string& str2) const {
    // Função para comparar strings ignorando maiúsculas e minúsculas
    return to_lower(str1) == to_lower(str2);
}

//consultar o horário de uma UC




//consultar o horário de uma UC/Turma
void Menu::consultarHorarioUCTurma() {
    string uccode;
    string classcode;

    cout << "--------------------------------------------------\n";
    cout << "Digite o Código da UC: ";
    cin >> uccode;
    cout << "Digite o Código da Turma: ";
    cin >> classcode;
    cout << endl;

    const vector<ClassUC>& todasAsTurmas = management_.getAllUC();
    bool encontrouTurma = false;

    for (const ClassUC& turma : todasAsTurmas) {
        if (correspondeCodigoUcETurma(turma, uccode, classcode)) {
            encontrouTurma = true;
            exibirHorarioDaTurma(turma);
        }
    }

    if (!encontrouTurma) {
        cout << "Código de UC ou Turma inválido." << endl;
    }
}

bool Menu::correspondeCodigoUcETurma(const ClassUC& turma, const string& uccode, const string& classcode) const {
    return (compararIgnorandoMaiusculas(turma.getUcCode(), uccode) && compararIgnorandoMaiusculas(turma.getClassCode(), classcode));
}

void Menu::exibirHorarioDaTurma(const ClassUC& turma) const {
    cout << turma.getUcCode() << " -- " << turma.getClassCode() << endl;
    for (const Slot& horario : turma.getSchedule()) {
        cout << '\t' << horario.getDay() << ' ' << horario.getStart() << ' ' << horario.getDuration() << ' ' << horario.getType() << '\n';
    }
}

//consultar o horário de uma UC/Turma




void Menu::consultarInformacoesAlunos() {
    cout << "╔═════════════════════════════════╗" << endl;
    cout << "║  Página de Consulta de Dados    ║" << endl;
    cout << "║           de Alunos             ║" << endl;
    cout << "║                                 ║" << endl;
    cout << "║ 1. Consultar alunos por turma   ║" << endl;
    cout << "║    ou ano                       ║" << endl;
    cout << "║ 2. Consultar número de          ║" << endl;
    cout << "║    estudantes inscritos em,     ║" << endl;
    cout << "║    pelo menos, n UCs            ║" << endl;
    cout << "║ 3. Voltar ao menu principal     ║" << endl;
    cout << "║                                 ║" << endl;
    cout << "╚═════════════════════════════════╝" << endl;
    cout << "Por favor, escolha uma opção (1-3): ";

    int escolha;
    cin >> escolha;

    switch (escolha) {
        case 1:
            consultarAlunosTurmaCursoAno();
            break;
        case 2: {
            int n;
            consultarNumEstudantesInscritosN_UC(n);
        }
            break;
        default:
            cout << "Escolha uma opção válida." << endl;
    }
}


void Menu::consultarAlunosTurmaCursoAno() {
    // Consultar alunos por turma ou ano.

    int opcao;
    cout << "╔════════════════════════════════╗" << endl;
    cout << "║  Página de Consulta de Alunos  ║" << endl;
    cout << "║        por Turma ou Ano        ║" << endl;
    cout << "║                                ║" << endl;
    cout << "║ 1. Consultar alunos por UCs    ║" << endl;
    cout << "║    e por turmas                ║" << endl;
    cout << "║ 2. Consultar alunos por ano    ║" << endl;
    cout << "║ 3. Voltar ao menu principal    ║" << endl;
    cout << "║                                ║" << endl;
    cout << "╚════════════════════════════════╝" << endl;

    cout << "Por favor, escolha uma opção (1-3): ";
    cin >> opcao;

    switch (opcao) {
        case 1:
            consultarAlunosPorTurma();
            break;
        case 2:
            consultarAlunosPorAno();
            break;
        case 3:
            // Voltar ao menu principal.
            break;
        default:
            cout << "Opção inválida." << endl;
            break;
    }
}





//Consultar alunos por UCs e por turmas
void Menu::consultarAlunosPorTurma() {
    cout << "Consulta de Alunos por UCs e Turmas" << endl;

    string ucCode;
    cout << "Por favor, insira o código da UC: ";
    cin >> ucCode;

    string classCode;
    cout << "Por favor, insira o código da turma: ";
    cin >> classCode;

    cout << "Alunos pertencentes à UC " << ucCode << " e à turma " << classCode << ":" << endl;

    bool alunosEncontrados = false;

    for (const Student& student : management_.getStudents()) {
        if (studentBelongsToUCAndClass(student, ucCode, classCode)) {
            alunosEncontrados = true;
            cout << "Nome do aluno: " << student.getName() << endl;
            cout << "Número de estudante: " << student.getCode() << endl;
            cout << endl;
        }
    }

    if (!alunosEncontrados) {
        cout << "Nenhum aluno encontrado para a UC e turma especificadas." << endl;
    }
}

bool Menu::studentBelongsToUCAndClass(const Student& student, const string& ucCode, const string& classCode) {
    for (const ClassUC& classUC : student.getclassUC()) {
        if (to_lower(classUC.getUcCode()) == to_lower(ucCode) &&
            to_lower(classUC.getClassCode()) == to_lower(classCode)) {
            return true;
        }
    }
    return false;
}
//Consultar alunos por UCs e por turmas






//Consultar alunos por Ano
void Menu::consultarAlunosPorAno() {
    cout << "Consultar alunos por ano (1-3)." << endl;

    char yearChar;
    cout << "Por favor, insira o ano (1-3): ";
    cin >> yearChar;
    cout << endl;

    if (yearChar >= '1' && yearChar <= '3') {
        for (const Student& student : management_.getStudents()) {
            for (const ClassUC& classUC : student.getclassUC()) {
                if (classUC.getClassCode().front() == yearChar) {
                    cout << "Nome do aluno: " << student.getName() << endl;
                    cout << "Número de estudante: " << student.getCode() << endl;
                    cout << "Código da Turma: " << classUC.getClassCode() << endl;
                    cout << endl;
                }
            }
        }
    } else {
        cout << "Ano inválido. Insira um ano de 1 a 3." << endl;
    }
}
//Consultar alunos por Ano




void Menu::consultarNumEstudantesInscritosN_UC(int n) {
    // consultar o número de estudantes inscritos em pelo menos n UCs.
    cout << "Digite o número mínimo de UCs:";
    cin >> n;
    int x = management_.studentregisterUCs(n);
    cout << "O numero de estudantes em pelo menos "<< n <<" UC's é: "  << x << endl;
}


void Menu::consultarTurmaAnoCursoUC() {

    int opcao;
    cout << "╔═══════════════════════════════════╗" << endl;
    cout << "║      Consultar UCs e Turmas       ║" << endl;
    cout << "║                                   ║" << endl;
    cout << "║ 1. Consultar as Turmas de uma UC  ║" << endl;
    cout << "║ 2. Consultar as Turmas de um ano  ║" << endl;
    cout << "║ 3. Consultar a UC com X ocupações ║" << endl;
    cout << "║ 4. Voltar ao menu principal       ║" << endl;
    cout << "║                                   ║" << endl;
    cout << "╚═══════════════════════════════════╝" << endl;
    cout << "Por favor, escolha uma opção (1-4): ";
    cin >> opcao;

    switch (opcao) {
        case 1:
            consultarTurmasUC();
            break;
        case 2:
            consultarUcDeUmAno();
            break;
        case 4:
            // Volte ao menu principal
            break;
        case 3:
            consultarUcComXOcupações();
            break;
        default:
            cout << "Opção inválida." << endl;
            break;
    }

}
void Menu::consultarTurmasUC() {
    string ucId;
    cout << "Por favor, insira o código da UC: " << endl;
    cin >> ucId;
    vector<ClassUC> turmasUc = management_.classOfUc(ucId);

    for (ClassUC &uc : turmasUc) {
        //std::cout << "UC Code: " << uc.getUcCode() << std::endl;
        std::cout << "Código da Turma: " << uc.getClassCode() << std::endl;
        cout << "-------------------------" << endl;
    }

    string ucCode;

    for (ClassUC &uc : turmasUc) {
        ucCode = uc.getUcCode();
    }

    std::cout << "Número de estudantes da UC: " << management_.numberStudentsUc(ucCode) << endl;
}


void Menu::consultarUcDeUmAno() {
    char ano;
    cout << "Por favor, insira o ano (1-3):" << endl;
    cin >> ano;

    if (ano < '1' || ano > '3') {
        cout << "Ano inválido. Insira um ano de 1 a 3." << endl;
        return;
    }

    vector<ClassUC> turmasUc = management_.classuC_x_year(ano);

    if (turmasUc.empty()) {
        cout << "Não foram encontradas UCs para o ano " << ano << "." << endl;
        return;
    }
    cout << "UCs do ano " << ano << ":" << endl;
    for (ClassUC &uc: turmasUc) {
        std::cout << "Código da UC: " << uc.getUcCode() << std::endl;
        std::cout << "Código da Turma: " << uc.getClassCode() << std::endl;
        std::cout << "Número de total de estudantes da UC (" << uc.getUcCode() <<") : " << management_.numberStudentsUc(uc.getUcCode()) << endl;
        cout << "-------------------------" << endl;
    }
}

void Menu::consultarUcComXOcupações() {
    int x;
    cout << "Por favor, insira o valor de ocupação desejado: ";
    cin >> x;

    vector<ClassUC> turmasUc = management_.ucWithXStudents(x);

    if (turmasUc.empty()) {
        cout << "Não foram encontradas UCs com " << x << " ou mais estudantes." << endl;
        return;
    }

    cout << "UCs com " << x << " ou mais estudantes:" << endl;

    for (const ClassUC &uc : turmasUc) {
        cout << "Código da UC: " << uc.getUcCode() << endl;
        cout << "Código da Turma: " << uc.getClassCode() << endl;
        cout << "Número de estudantes: " << management_.numberStudentsUc(uc.getUcCode()) << endl;
        cout << "-------------------------" << endl;
    }
}


void Menu::realizarAlteracoes() {
    int choice;
    do {
        // Menu da Página de Realização de Alterações
        cout << "╔════════════════════════════════╗" << endl;
        cout << "║  Página de Realização de       ║" << endl;
        cout << "║  Alterações                    ║" << endl;
        cout << "║                                ║" << endl;
        cout << "║ 1. Realizar alterações em UC   ║" << endl;
        cout << "║ 2. Realizar alterações em      ║" << endl;
        cout << "║    turmas                      ║" << endl;
        cout << "║ 3. Voltar ao menu principal    ║" << endl;
        cout << "║                                ║" << endl;
        cout << "╚════════════════════════════════╝" << endl;
        cout << "Por favor, escolha uma opção (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                realizarAlteracoesUC();
                break;
            case 2:
                realizarAlteracoesTurma();
                break;
            case 3:
                cout << "A voltar ao menu principal." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-3)." << endl;
                break;
        }
    } while (choice != 3);
}

void Menu::realizarAlteracoesUC() {
    int choice;
    do {
        // Menu de Alterações nas UCs
        cout << "╔═══════════════════════════════════╗" << endl;
        cout << "║  Realizar Alterações nas UCs      ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "║ 1. Ingressar numa UC              ║" << endl;
        cout << "║ 2. Sair de uma UC                 ║" << endl;
        cout << "║ 3. Voltar ao menu principal       ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "╚═══════════════════════════════════╝" << endl;
        cout << "Por favor, escolha uma opção (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                ingressarEmUC();
                break;
            case 2:
                sairDeUC();
                break;
            case 3:
                cout << "A voltar ao menu principal." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-3)." << endl;
                break;
        }
    } while (choice != 3);
}


void Menu::ingressarEmUC() {

}






void Menu::sairDeUC() {

}


void Menu::realizarAlteracoesTurma() {

}



void Menu::visualizarHistoricoPedidos() {

}

void Menu::processarPedidos() {

}

