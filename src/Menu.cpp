#include "Menu.h"
#include "DataManager.h"


#include <iostream>

/**
 * @brief Constructor for the Menu class
 *
 * @param management
 *
 * Time Complexity: O(1)
 */
Menu::Menu(DataManager& management) : management_(management), requestManager_(management) {
}

/**
 * @brief set the DataManager for the Menu
 *
 * @param management reference to the DataManager object
 *
 * Time Complexity O(1)
 */

void Menu::setManagement(const DataManager &management) {
    management_ = management;
}

/**
 * @brief function to convert string to lowercase
 *
 * @param str input string
 *
 * @return The input string converted to lowercase
 *
 * Time Complexity: O(n), where n is the length of the input string.
 *
 */
string to_lower (string str)
{
    for(auto& elem : str)
    {elem = tolower(elem);}
    return str;
}

/**
 * @brief Start the main menu loop
 *
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
 *
 * @brief Display the menu to consult schedules
 *
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
 *
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
 *
 * @param student student object whose schedule should be displayed.
 *
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
 *
 * Time complexity O(n) where n is the number of slots.
 *
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
        displayClassUcSchedule(ucS,classUc1);
    }
}

/**
 * @brief function to indicating a valid class code.
 *
 * @param ucS slots associated with a class code.
 *
 * @return True if ucS is empty, or false if its not empty
 *
 * Time complexity O(1)
 */
bool Menu::isClassCodeValid(const vector<Slot>& ucS) const {
    return ucS.empty();
}
/**
 * @brief function to Display the schedule of  a specific ClassUc
 *
 * @param ucS
 *
 * @param classUc
 *
 * Time complexity O(n), where 'n' is the number of slots in the provided 'ucS' vector.
 *
 */
void Menu::displayClassUcSchedule(const vector<Slot>& ucS,const ClassUC& classUc) const {
    cout << "UcCode:"<< classUc.getUcCode()<<"||"<<"ClassCode:"<<classUc.getClassCode()<<  endl;
    for (const Slot& a : ucS) {
        cout << '\t' << a.getDay() << ' ' << a.getStart() << ' ' << a.getDuration() << ' ' << a.getType() << '\n';
    }
}
//consultar o horário de uma turma



//consultar o horário de uma UC
/**
 * @brief Function to consult the schedule of a specific UC.
 *
 * Time complexity O(1)
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
 * @brief function to checks if the given ClassUC corresponds to the specified UC code
 *
 * @param turma The ClassUC object to compare
 *
 * @param ucCode The UC code to check for correspondence
 *
 * @return True if th Uc code corresponds, false otherwise
 *
 * Time complexity O(n), where 'n' is the length of the input string ucCode
 */
bool Menu::correspondeCodigoUC(const ClassUC& turma, const string& ucCode) const {
    return compararIgnorandoMaiusculas(turma.getUcCode(), ucCode);
}

/**
 * @brief function to display the schedule for a specific UC
 *
 * @param ucS The vector of Slot objects representing the UC schedule
 *
 * @param ucCode The code of the UC for which the schedule is displayed
 *
 * Time complexity is O(n), where 'n' is the number of Slot objects in the ucS
 */
void Menu::exibirHorarioDaUC(const vector<Slot> ucS,string ucCode) const {
    cout << ucCode<< endl;
    for (const Slot& horario : ucS) {
        cout << '\t' << horario.getDay() << ' ' << horario.getStart() << ' ' << horario.getDuration() << ' ' << horario.getType() << '\n';
    }
}

/**
 * @brief function to compare two strings
 *
 * @param str1 the first string to compare
 *
 * @param str2 the second string to compare
 *
 * @return True if the two strings are equal, false otherwise.
 *
 * Time complexity  O(n), where 'n' is the length of the longer of the two input strings.
 */
bool Menu::compararIgnorandoMaiusculas(const string& str1, const string& str2) const {
    // Função para comparar strings ignorando maiúsculas e minúsculas
    return to_lower(str1) == to_lower(str2);
}

//consultar o horário de uma UC




//consultar o horário de uma UC/Turma
/**
 * @brief function to consult the schedule of a class
 *
 * Time complexity O(n), where 'n' is the number of slots in the class schedule.
 */
void Menu::consultarHorarioTurma() {
    string classcode;

    cout << "--------------------------------------------------\n";
    cout << "Digite o Código da Turma: ";
    cin >> classcode;
    cout << endl;
    const vector<ClassUC>& ucS = management_.getCLass(classcode);
    if (ucS.empty()) {
        cout << "That's not a valid input." << endl;}
    else{
        displayClassSchedule(ucS,classcode);
    }

}


/**
 * @brief this function checks if the given ClassUC corresponds to the specified UC code and class code
 *
 * @param turma The ClassUC object to compare
 *
 * @param uccode The UC code to check
 *
 * @param classcode The class code to check
 *
 * @return True if the UC code and class code match (case-insensitive), false otherwise
 *
 * Time complexity  O(n), where 'n' is the length of the longer of the two input strings.
 */
bool Menu::correspondeCodigoUcETurma(const ClassUC& turma, const string& uccode, const string& classcode) const {
    return (compararIgnorandoMaiusculas(turma.getUcCode(), uccode) && compararIgnorandoMaiusculas(turma.getClassCode(), classcode));
}


/**
 * @brief function to displays the schedule for a specific class
 *
 * @param ucS The vector of Slot objects representing the class schedule.
 *
 * @param turma The code of the class for which the schedule is displayed.
 *
 * Time complexity O(n), where 'n' is the number of Slot objects in the ucS
 */
void Menu::displayClassSchedule(const vector<ClassUC>& ucS,const string& turma) const {
    ClassUC prevClass;
    cout << "class code:"<<turma << endl;
    for(const ClassUC classes :ucS) {
        cout<<"Uc code is:"<<classes.getUcCode()<<endl;
        for (const Slot &horario: classes.getSchedule()) {
            cout << '\t' << horario.getDay() << ' ' << horario.getStart() << ' ' << horario.getDuration() << ' '
                 << horario.getType() << '\n';
        }
    }
}

//consultar o horário de uma UC/Turma



/**
 * @brief function to displays a menu for the student information.
 *
 * Time complexity O(1)
 */
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

/**
 * @brief function to consult and display the classes of a specific student.
 *
 * Time complexity O(n), where 'n' is the number of students in the system.
 */
void Menu::consultarTurmasDoAluno() {
    int id;
    string name;
    cout << "--------------------------------------------------\n";
    cout << "Introduza o número UP:"<< endl;
    cin >> id;
    cout << "Introduza o nome do estudante:"<< endl;
    cin >>name;
    cout << endl;
    Student student=Student(id,name);
    student=management_.findStudent(student);
    for(auto a:student.getclassUC()){
        a.print();
    }
}

string Menu::Student_sort_type() {
    int opcao;
    cout << "╔════════════════════════════════╗" << endl;
    cout << "║  Página de escolha do tipo de  ║" << endl;
    cout << "║      organizaçao dos alunos    ║" << endl;
    cout << "║                                ║" << endl;
    cout << "║ 1. Ordem alfabetica            ║" << endl;
    cout << "║ 2. Ordem alfabetica reverse    ║" << endl;
    cout << "║ 3. Ordem numerica              ║" << endl;
    cout << "║ 4. Ordem numerica reverse      ║" << endl;
    cout << "║                                ║" << endl;
    cout << "╚════════════════════════════════╝" << endl;

    cout << "Por favor, escolha uma opção (1-4): ";
    cin >> opcao;
    switch (opcao) {
        case 1:
            return "alphabetical";
            break;
        case 2:
            return "reverse alphabetical";
            break;
        case 3:
            return "numerical";
            break;
        case 4:
            return "reverse numerical";
            break;

        default:
            cout << "Opção inválida." << endl;
            return  "";
            break;

    }

}



/**
 * @brief Function to consult students by class or year.
 *
 * Time complexity O(1)
 */
void Menu::consultarAlunosTurmaCursoAno() {
    // Consultar alunos por turma ou ano.
    string type=Student_sort_type();
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
            consultarAlunosPorTurma(type);
            break;
        case 2:
            consultarAlunosPorAno(type);
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
/**
 * @brief function to consult and displays students belonging to a specific UC and class.
 *
 * Time complexity O(n), where 'n' is the number of students in the system
 */
void Menu::consultarAlunosPorTurma(string type) {
    cout << "Consulta de Alunos por UCs e Turmas" << endl;

    string ucCode;
    cout << "Por favor, insira o código da UC: "<< endl;
    cin >> ucCode;

    string classCode;
    cout << "Por favor, insira o código da turma: "<< endl;
    cin >> classCode;
    ClassUC classUc=ClassUC(ucCode,classCode);

    cout << "Alunos pertencentes à UC " << ucCode << " e à turma " << classCode << ":" << endl;
    vector<Student> students=management_.studentsOfClassUc(classUc);
    management_.sortStudent(students,type);
    for (const Student& student : students) {
            cout << "Nome do aluno: " << student.getName() << endl;
            cout << "Número de estudante: " << student.getCode() << endl;
            cout << endl;
    }
    if(students.empty()){
        cout << "Nenhum aluno encontrado para a UC e turma especificadas." << endl;
    }

}

/**
 * @brief this function checks if a student belongs to a specific UC and class within that Uc.
 *
 * @param student The student to check for enrollment.
 *
 * @param ucCode The code of the UC to check for.
 *
 * @param classCode The code of the class within the UC to check for.
 *
 * @return True if the student belongs to the specific Uc and class, false otherwise
 *
 * Time complexity O(n), where 'n' is the number of ClassUC
 */
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
/**
 * @brief Function to consult and display students based on the specified academic year
 *
 * Time complexity O(n * m), where 'n' is the number of students in the system and 'm' is the average number of classes per student
 */
void Menu::consultarAlunosPorAno(string type) {
    cout << "Consultar alunos por ano (1-3)." << endl;

    char yearChar;
    cout << "Por favor, insira o ano (1-3): ";
    cin >> yearChar;
    cout << endl;

    if (yearChar >= '1' && yearChar <= '3') {
        vector<Student> students=management_.studentYear(yearChar);
        management_.sortStudent(students,type);
        for (const Student& student : students) {
            cout << "Nome do aluno: " << student.getName() << endl;
            cout << "Número de estudante: " << student.getCode() << endl;
            cout << endl;
        }
    }
    else {
        cout << "Ano inválido. Insira um ano de 1 a 3." << endl;
    }
}
//Consultar alunos por Ano



/**
 * @brief function to consult and display the number of students registered in at least 'n' UCs.
 *
 * @param n The minimum number of UCs a student must be registered in to be counted.
 *
 * Time complexity O(n), where 'n' is the number of students in the system.
 */
void Menu::consultarNumEstudantesInscritosN_UC(int n) {
    // consultar o número de estudantes inscritos em pelo menos n UCs.
    cout << "Digite o número mínimo de UCs:";
    cin >> n;
    int x = management_.studentregisterUCs(n);
    cout << "O numero de estudantes em pelo menos "<< n <<" UC's é: "  << x << endl;
}

/**
 * @brief this function allows the user to choose between different options on the menu of the course
 *
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
 *
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
 *
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
 * @brief function to consult UCs with a minimum number of students
 *
 * Time complexity: O(n), where 'n' is the number of UCs with student occupancy greater than or equal to 'x'.
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

    cout << "UCs com " << x << "estudantes:" << endl;

    for (const ClassUC &uc : turmasUc) {
        cout << "Código da UC: " << uc.getUcCode() << endl;
        cout << "Código da Turma: " << uc.getClassCode() << endl;
        cout << "Número de estudantes: " << management_.numberStudentsUc(uc.getUcCode()) << endl;
        cout << "-------------------------" << endl;
    }
}

/**
 * @brief function to display a menu for performing various types of changes.
 *
 * Time complexity O(1)
 */
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

/**
 * @brief this function allows the user to perform changes related to UCs.
 *
 * Time complexity O(1)
 */
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

/**
 * @brief this function allows a student to enroll in a specific UC if eligible
 *
 * Time complexity O(n), where 'n' represents the number of students in the system.
 */
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


/**
 * @brief this function finds and return a ClassUC object for a given UC code associated with a student.
 *
 * @param student The student for whom to find the ClassUC object
 *
 * @param uc_code The UC code to search for
 *
 * @param manager The DataManager containing the data
 *
 * @return A ClassUC object with the matching UC code, or a null ClassUC object if not found
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects associated with the student
 */
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

/**
 * @brief this function allows a student to leave  a specific UC
 *
 * Time complexity O(1)
 */
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

/**
 * @brief Allows the user to perform various class-related operations such as joining, leaving, or changing classes
 *
 * Time complexity O(n), where 'n' is the number of available classes.
 *
 */
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

/**
 * @brief Allows a student to join a specific class
 *
 * Time complexity O(n), where 'n' where 'n' represents the number of students in the system
 */
void Menu::ingressarNumaTurma() {
    int upNumber;string studentName;
    cout << "Digite o número UP do estudante: "<<endl;;
    cin >> upNumber;
    cout <<"Digite o nome de estudante: "<<endl;;
    cin>>studentName;
    string ucCode,classCode;
    cout << "Digite o código UC da turma da qual o estudante deseja entrar: "<<endl;;
    cin >> ucCode;
    cout << "Digite o código da turma da qual o estudante deseja entrar: "<<endl;;
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



/**
 *  @brief this function allows a student to change from one class to another in a specific UC
 *
 * Time complexity O(n), where 'n' is the number of classes
 */
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

/**
 *  @brief this function allows a student to leave a specific class in a  specific UC
 *
 * Time complexity O(n), where 'n' is the number of classes
 */
void Menu::sairDeUmaTurma() {
    int upNumber;string studentName;
    cout << "Digite o número UP do estudante: "<<endl;;
    cin >> upNumber;
    cout <<"Digite o nome de estudante: "<<endl;;
    cin>>studentName;
    string ucCode,classCode;
    cout << "Digite o código UC da turma da qual o estudante deseja sair: "<<endl;;
    cin >> ucCode;
    cout << "Digite o código da turma da qual o estudante deseja sair: "<<endl;;
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
/**
 * @brief this function allows to visualize the history of requests
 *
 * Time complexity O(n), where 'n' is the number of requests in each queue.
 */
void Menu::visualizarHistoricoPedidos() {
    requestManager_.showAllChanges();

}

/**
 * @brief this function process the requests
 *
 * Time complexity O(1)
 */
void Menu::processarPedidos() {
  DataManager newManager;
  if(requestManager_.getRequest().empty()){
      cout<<"Não há pedidos para processar"<<endl;
  }
  else {
      requestManager_.requestProcess(newManager);
      management_=newManager;
        cout<<"Pedido processado com sucesso"<<endl;
  }
}

/**
 * @brief this function allows confirming or canceling alterations to classes.
 *
 * Time complexity O(1)
 */
void Menu::confirmar_cancelar(){
    int choice;
    do {

        cout << "╔═══════════════════════════════════╗" << endl;
        cout << "║  Realizar Alterações nas turma    ║" << endl;
        cout << "║                                   ║" << endl;
        cout << "║ 1. Aceitar alterações             ║" << endl;
        cout << "║ 2. Cancelar alterações/fechar     ║" << endl;
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


/**
 * @brief this function undoes all pending changes to the class schedule.
 *
 *  Time complexity: O(n) where 'n' is the number of requests processed  of pending changes
 */
void Menu::undoPedidos() {
    DataManager newManager;
    requestManager_.processUndoRequest(newManager);
    management_=newManager;
    cout <<"Todas as alterações foram canceladas."<<endl;

}
/**
 * @brief this function writes alteration
 */
void Menu::escrver_alteraçoes() {
    char result;
    cout<<"Pretendes aceitar as alterações feitas?"<<endl;
    cout<<"Quando aceitares,não podes cancelar as alteraçoes feitas"<<endl;
    cout<<"S/N:"<<endl;;
    cin >>result;
    if(result=='N' or result=='n'){
        confirmar_cancelar();
    }
    else{
        cout<<"Alterações realizadas com sucesso"<<endl;;
        requestManager_.writeFiles();
        cout<<"O programa vai fechar"<<endl;
        exit(0);
    }


}




