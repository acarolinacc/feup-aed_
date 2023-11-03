#include "Menu.h"
#include "DataManager.h"


#include <iostream>

/**
 * @brief Constructor for the Menu class
 * @param management
 * Time Complexity: O(1)
 */
Menu::Menu(DataManager& management) : management_(management), requestManager_(management) {
}

/**
 * @brief set the DataManager for the Menu
 * @param management reference to the DataManager object
 * Time Complexity O(1)
 */

void Menu::setManagement(const DataManager &management) {
    management_ = management;
}

/**
 * @brief function to convert string to lowercase
 * @param str input string
 * @return The input string converted to lowercase
 * Time Complexity: O(n), where n is the length of the input string.
 */
string to_lower (string str)
{
    for(auto& elem : str)
    {elem = tolower(elem);}
    return str;
}

/**
 * @brief Start the main menu loop
 * Time Complexity: O(n), where n is the number of iterations in the main menu loop.
 */
void Menu::start() {
    management_.readStudentClasses();
    management_.readClasses();
    requestManager_.setManager(management_);
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
        cout << "║ 7. confirmar/cancelar alterações║" << endl;
        cout << "║ 8. Sair do programa             ║" << endl;
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
                confirmar_cancelar();
                break;
            case 8:
                cout << "A sair do programa." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-7)." << endl;
                break;
        }
    } while (choice != 8);
}

/**
 * @brief Display the menu to consult schedules
 * Time Complexity: O(n), where n is the number of iterations in the schedule consultation menu loop.
 */
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
/**
 * @brief funtion to consult schedule of the student
 * Time complexity O(n) where n is the number of students in the system, as it may require searching for the student by UP number and name.
 */
void Menu::consultarHorarioAluno() {
    int id;
    string name;
    cout << "--------------------------------------------------\n";
    cout << "Introduza o número UP:";
    cin >> id;
    cout << "Introduza o nome do estudante:";
    cin >>name;
    cout << endl;
    Student student=Student(id,name);
    Student wanted = management_.getStudentSchedule(student);
    displayStudentSchedule(wanted);
}

/**
 * @brief function to display thr schedule of a student
 * @param student student object whose schedule should be displayed.
 * Time complexity O(n), where n is the total number of slots in the schedule.
 */
void Menu::displayStudentSchedule(const Student &student) const{
    if (student.getCode() != 0) {
        for (const ClassUC& classUc : student.getclassUC()) {
            cout << classUc.getUcCode() << "|" << classUc.getClassCode()<<endl;
            map<ClassUC, vector<Slot>> d=student.getSchedule();
            for (const Slot& a :d[classUc] ) {

                cout << '\t' << a.getDay() << ' ' << a.getStart() << ' ' << a.getDuration() << ' ' << a.getType() << '\n';
            }
        }
    } else {
        cout << "Numero ou nome do estudante invalido" << endl;
    }
}

//consultar o horário de um aluno



//consultar o horário de uma turma
/**
 * @brief function to consult the schedule of a Turma
 * Time complexity O(n) where n is the number of slots.
 */
void Menu::consultarHorarioUCTurma() {
    string classCode;
    string ucCode;
    cout << "--------------------------------------------------\n";
    cout << "Por favor, insira o código da turma:";
    cin >> classCode;
    cout << "Por favor, insira o código da Uc:";
    cin >> ucCode;
    cout << endl;
    ClassUC classUc1=ClassUC(ucCode,classCode);
    const vector<Slot>& ucS = management_.getClassUCSchedule(classUc1);
    if (isClassCodeValid(ucS)) {
        cout << "That's not a valid input." << endl;}
    else{
        cout << ucS.size();
        displayClassUcSchedule(ucS,classUc1);
    }
}

/**
 * @brief
 * @param ucS slots associated with a class code.
 * @return True if ucS is empty, or false if its not empty
 */
bool Menu::isClassCodeValid(const vector<Slot>& ucS) const {
    return ucS.empty();
}
/**
 *
 * @param ucS
 * @param classUc
 */
void Menu::displayClassUcSchedule(const vector<Slot>& ucS,const ClassUC& classUc) const {
    cout << "UcCode:"<< classUc.getUcCode()<<"ClassCode:"<<classUc.getClassCode()<<  endl;
    for (const Slot& a : ucS) {
        cout << '\t' << a.getDay() << ' ' << a.getStart() << ' ' << a.getDuration() << ' ' << a.getType() << '\n';
    }
}
//consultar o horário de uma turma



//consultar o horário de uma UC
/**
 *
 */
void Menu::consultarHorarioUC() {
    string ucCode;

    cout << "--------------------------------------------------\n";
    cout << "Digite o Código da UC: ";
    cin >> ucCode;
    cout << endl;
    const vector<Slot>& ucS = management_.getUcSchedule(ucCode);
    if (ucS.empty()) {
        cout << "Código de UC inválido." << endl;
    }
    else{
        exibirHorarioDaUC(ucS,ucCode);
    }

}

/**
 *
 * @param turma
 * @param ucCode
 * @return
 */
bool Menu::correspondeCodigoUC(const ClassUC& turma, const string& ucCode) const {
    return compararIgnorandoMaiusculas(turma.getUcCode(), ucCode);
}

/**
 *
 * @param ucS
 * @param ucCode
 */
void Menu::exibirHorarioDaUC(const vector<Slot> ucS,string ucCode) const {
    cout << ucCode<< endl;
    for (const Slot& horario : ucS) {
        cout << '\t' << horario.getDay() << ' ' << horario.getStart() << ' ' << horario.getDuration() << ' ' << horario.getType() << '\n';
    }
}

/**
 *
 * @param str1
 * @param str2
 * @return
 */
bool Menu::compararIgnorandoMaiusculas(const string& str1, const string& str2) const {
    // Função para comparar strings ignorando maiúsculas e minúsculas
    return to_lower(str1) == to_lower(str2);
}

//consultar o horário de uma UC




//consultar o horário de uma UC/Turma
/**
 *
 */
void Menu::consultarHorarioTurma() {
    string classcode;

    cout << "--------------------------------------------------\n";
    cout << "Digite o Código da Turma: ";
    cin >> classcode;
    cout << endl;
    const vector<Slot>& ucS = management_.getClassSchedule(classcode);
    if (isClassCodeValid(ucS)) {
        cout << "That's not a valid input." << endl;}
    else{
        displayClassSchedule(ucS,classcode);
    }

}


/**
 *
 *
 * @param turma
 * @param uccode
 * @param classcode
 * @return
 */
bool Menu::correspondeCodigoUcETurma(const ClassUC& turma, const string& uccode, const string& classcode) const {
    return (compararIgnorandoMaiusculas(turma.getUcCode(), uccode) && compararIgnorandoMaiusculas(turma.getClassCode(), classcode));
}

void Menu::displayClassSchedule(const vector<Slot>& ucS,const string& turma) const {
    cout << "class code:"<<turma << endl;
    for (const Slot& horario : ucS) {
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
    cout << "║ 3. Consultar turmas de um aluno ║" << endl;
    cout << "║ 4. Voltar ao menu principal     ║" << endl;
    cout << "║                                 ║" << endl;
    cout << "╚═════════════════════════════════╝" << endl;
    cout << "Por favor, escolha uma opção (1-4): ";

    int escolha;
    cin >> escolha;

    switch (escolha) {
        case 1:
            consultarAlunosTurmaCursoAno();
            break;
        case 2: {
            int n;
            consultarNumEstudantesInscritosN_UC(n);
            break;
        }
        case 3:{
            consultarTurmasDoAluno();
            break;

        }
        default:
            cout << "Escolha uma opção válida." << endl;
    }
}

void Menu::consultarTurmasDoAluno() {
    int id;
    string name;
    cout << "--------------------------------------------------\n";
    cout << "Introduza o número UP:";
    cin >> id;
    cout << "Introduza o nome do estudante:";
    cin >>name;
    cout << endl;
    Student student=Student(id,name);
    student=management_.findStudent(student);
    for(auto a:student.getclassUC()){
        a.print();
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

/**
 * @brief this function allows the user to choose between different options on the menu of the course
 * Time complexity O(1)
 */
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
/**
 * @brief function to consult the class of Uc
 * Time complexity: O(n + m), where 'n' is the number of ClassUC objects retrieved for the specified UC, and 'm' is the time complexity of fetching the total number of students for that UC.
 */

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
/**
 * @brief function to consult Uc of a year
 * Time complexity: O(n + m), where 'n' is the number of ClassUC objects retrieved for the specified year, and 'm' is the sum of the time complexity of fetching UC information for each ClassUC object.
 */

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
/**
 * @brief
 */
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
    cout << "--------------------------------------------------\n";
    int upNumber;
    string studentName;
    cout << "Digite o número UP do estudante: ";
    cin >> upNumber;
    cout <<"Digite o nome de estudante: ";
    cin>>studentName;
    string ucCode;
    cout << "Digite o código da UC da qual o estudante deseja entrar: ";
    cin >> ucCode;
    Student student=Student(upNumber,studentName);
    student=management_.findStudent(student);//students got the classes
    ClassUC classUc=ClassUC(ucCode,"");
    Request request=Request(student,classUc,"EU");
    if (requestManager_.ingressarEmUC(upNumber, ucCode)) {
        cout << "O pedido do estudante foi aceite:" << ucCode << endl;
        requestManager_.addResquest(request);
    } else {
        cout << "Não foi possível ingressar na UC " << ucCode << ". Verifique as regras e a disponibilidade de vagas." << endl;
    }
}

ClassUC findCLassByuc(Student student,string uc_code,DataManager manager){
    ClassUC null;
    student=manager.findStudent(student);
    for(ClassUC classuc:student.getclassUC()){
        if(classuc.getUcCode()==uc_code){
            return classuc;
        }

    }
    return  null;
}

void Menu::sairDeUC() {
    int upNumber;
    string studentName;
    cout << "Digite o número UP do estudante: ";
    cin >> upNumber;
    cout <<"Digite o nome de estudante: ";
    cin>>studentName;
    string ucCode;
    cout << "Digite o código da UC da qual o estudante deseja sair: ";
    cin >> ucCode;
    Student student=Student(upNumber,studentName);
    student=management_.findStudent(student);//students got the classes

    ClassUC classUc= findCLassByuc(student,ucCode,management_); //just to be easier to undo the uc request
    Request request=Request(student,classUc,"SU");
    if (requestManager_.sairDeUC(upNumber, ucCode)) {
        cout << "Pedido aceite com sucesso ." << endl;
        requestManager_.addResquest(request);
    } else {
        cout << "Falha ao sair da UC. Verifique os dados inseridos." << endl;
    }
}

void Menu::realizarAlteracoesTurma() {
    int choice;
    do {

        cout << "╔═══════════════════════════════════╗" << endl;
        cout << "║  Realizar Alterações nas turma    ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "║ 1. Ingressar numa turma           ║" << endl;
        cout << "║ 2. Sair de uma turma              ║" << endl;
        cout << "║ 3. Mudar de turmar                ║" << endl;
        cout << "║ 4. Voltar ao menu principal       ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "╚═══════════════════════════════════╝" << endl;
        cout << "Por favor, escolha uma opção (1-3): ";
        cin >> choice;


        switch (choice) {
            case 1:
                ingressarNumaTurma();
                break;
            case 2:
                sairDeUmaTurma();
                break;
            case 3:
                mudarDeTurma();
                break;
            case 4:
                cout << "A voltar ao menu principal." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-4)." << endl;
                break;
        }

    } while (choice!=4);
}
void Menu::ingressarNumaTurma() {
    int upNumber;string studentName;
    cout << "Digite o número UP do estudante: ";
    cin >> upNumber;
    cout <<"Digite o nome de estudante: ";
    cin>>studentName;
    string ucCode,classCode;
    cout << "Digite o código UC da turma da qual o estudante deseja entrar: ";
    cin >> ucCode;
    cout << "Digite o código da turma da qual o estudante deseja entrar: ";
    cin >> classCode;
    Student student=Student(upNumber,studentName);
    student=management_.findStudent(student);//students got the classes
    ClassUC classUc=ClassUC(ucCode,classCode);
    Request request=Request(student,classUc,"EC");
    if(requestManager_.checkClassRequest(request)){
        cout<<"Solicitação válida!"<<endl;
        requestManager_.addResquest(request);
    }
    else{cout<<"Solicitação inválida, faça outra solicitação."<<endl;}
}




void Menu::mudarDeTurma() {//this type of request is 2 request in one:
    int upNumber;string studentName;
    cout << "Digite o número UP do estudante: "<<endl;
    cin >> upNumber;
    cout <<"Digite o nome de estudante: "<<endl;
    cin>>studentName;
    Student student=Student(upNumber,studentName);
    student=management_.findStudent(student);//students got the classes
    string ucCode,classCode;
    cout << "Digite o código UC da turma da qual o estudante deseja sair: "<<endl;
    cin >> ucCode;
    cout << "Digite o código da turma da qual o estudante deseja sair: "<<endl;
    cin >> classCode;
    ClassUC old_classUc=ClassUC(ucCode,classCode);
    Request request=Request(student,old_classUc,"SC");
    if(requestManager_.checkClassRequest(request)){
        cout<<"Valid request"<<endl;
        requestManager_.addResquest(request);
        cout << "Digite o código UC da turma da qual o estudante deseja entrar: "<<endl;
        cin >> ucCode;
        cout << "Digite o código da turma da qual o estudante deseja entrar: "<<endl;
        cin >> classCode;
        ClassUC new_classUc=ClassUC(ucCode,classCode);
        Request request2=Request(student,new_classUc,"EC");
        if(requestManager_.checkClassRequest(request2)){
            cout<<"Valid request"<<endl;
            requestManager_.addResquest(request2);
        }
        else{ cout<<"Solicitação inválida, faça outra solicitação."<<endl;}

    }

    else{
        cout<<"Solicitação inválida, faça outra solicitação."<<endl;
    }
}
void Menu::sairDeUmaTurma() {
    int upNumber;string studentName;
    cout << "Digite o número UP do estudante: ";
    cin >> upNumber;
    cout <<"Digite o nome de estudante: ";
    cin>>studentName;
    string ucCode,classCode;
    cout << "Digite o código UC da turma da qual o estudante deseja sair: ";
    cin >> ucCode;
    cout << "Digite o código da turma da qual o estudante deseja sair: ";
    cin >> classCode;
    Student student=Student(upNumber,studentName);
    student=management_.findStudent(student);//students got the classes
    ClassUC classUc=ClassUC(ucCode,classCode);
    Request request=Request(student,classUc,"SC");
    if(requestManager_.checkClassRequest(request)) {
        cout<<"Valid request"<<endl;
        requestManager_.addResquest(request);
    }
    else{
        cout<<"Solicitação inválida, faça outra solicitação."<<endl;
    }

}
void Menu::visualizarHistoricoPedidos() {
    requestManager_.showAllChanges();

}

void Menu::processarPedidos() {
  DataManager newManager;
    if(requestManager_.getRequest().empty()){
      cout<<"Não há pedidos para processar"<<endl;
  }
  else {
      requestManager_.requestProcess(newManager);
      management_=newManager;
  }
}

void Menu::confirmar_cancelar(){
    int choice;
    do {

        cout << "╔═══════════════════════════════════╗" << endl;
        cout << "║  Realizar Alterações nas turma    ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "║ 1. Aceitar alterações             ║" << endl;
        cout << "║ 2. Cancelar alterações            ║" << endl;
        cout << "║ 3. Voltar ao menu principal       ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "╚═══════════════════════════════════╝" << endl;
        cout << "Por favor, escolha uma opção (1-3): ";
        cin >> choice;


        switch (choice) {
            case 1:
                escrver_alteraçoes();
                break;
            case 2:
                undoPedidos();
                break;
            case 3:
                cout << "A voltar ao menu principal." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, escolha uma opção válida (1-4)." << endl;
                break;
        }

    } while (choice!=3);
}



void Menu::undoPedidos() {
    DataManager newManager;
    requestManager_.processUndoRequest(newManager);
    management_=newManager;
    cout <<"Todas as alterações foram canceladas."<<endl;

}

void Menu::escrver_alteraçoes() {

}



