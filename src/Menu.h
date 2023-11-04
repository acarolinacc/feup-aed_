
#ifndef MENU_H
#define MENU_H

#include "DataManager.h"
#include "RequestManager.h"

/**
 * @brief function for user interface to show the menu
 */
class Menu {
public:
    void setManagement(const DataManager &management);
    Menu(DataManager& management);
    void start();
    void consultarHorarios();

    void consultarHorarioAluno();
    void consultarHorarioTurma();
    void consultarHorarioUC();
    void consultarHorarioUCTurma();
    bool studentBelongsToUCAndClass(const Student& student, const string& ucCode, const string& classCode);
    void realizarAlteracoes();




    void consultarInformacoesAlunos();

    void consultarAlunosPorTurma();
    void consultarAlunosPorAno();
    void consultarNumEstudantesInscritosN_UC(int n);
    void consultarTurmasDoAluno();

    void consultarAlunosTurmaCursoAno();
    void consultarTurmaAnoCursoUC();
    void  consultarTurmasUC();
    void consultarUcDeUmAno();
    void consultarUcComXOcupações();

    bool isClassCodeValid(const vector<Slot>& ucS) const;
    void displayClassUcSchedule( const vector<Slot>& ucS,const ClassUC& classUc) const;


    void displayStudentSchedule(const Student &student) const;
    bool correspondeCodigoUcETurma(const ClassUC &turma, const string &uccode, const string &classcode) const;
    void displayClassSchedule(const vector<Slot>& ucS,const string& turma) const;
    void exibirHorarioDaUC(const vector<Slot> ucS,string ucCode) const;
    bool compararIgnorandoMaiusculas(const string &str1, const string &str2) const;
    bool correspondeCodigoUC(const ClassUC &turma, const string &ucCode) const;




    void ingressarEmUC();
    void sairDeUC();
    void realizarAlteracoesUC();



    void realizarAlteracoesTurma();
    void ingressarNumaTurma();
    void sairDeUmaTurma();
    void mudarDeTurma();


    void confirmar_cancelar();
    void escrver_alteraçoes();
    void visualizarHistoricoPedidos();
    void processarPedidos();
    void undoPedidos();



    //not use functions
    void printStudentInfo(const Student& student);
    bool areStringsEqualIgnoreCase(const std::string& str1, const std::string& str2);
    bool isNameOrUpValid(const string &input, const string &name, const string &upNumber) const;
    void displayClassHorario(const ClassUC &uc) const;
    void consultarUcsComMaisEstudantes();
    bool isStudentValid(const string &input, const Student &student) const;
    void consultarInformacoesUCs();

private:
    RequestManager requestManager_;
    DataManager management;

    DataManager& management_;


};

#endif

