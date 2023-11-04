
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

    void consultarAlunosPorTurma(string type);
    void consultarAlunosPorAno(string type);
    void consultarNumEstudantesInscritosN_UC(int n);
    void consultarTurmasDoAluno();

    void consultarAlunosTurmaCursoAno();
    void consultarTurmaAnoCursoUC();
    void  consultarTurmasUC();
    void consultarUcDeUmAno();
    void consultarUcComXOcupações();
    string Student_sort_type();

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





private:
    RequestManager requestManager_;
    DataManager management;

    DataManager& management_;


};

#endif

