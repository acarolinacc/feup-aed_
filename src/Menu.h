#ifndef MENU_H
#define MENU_H

#include "DataManager.h"

class Menu {
public:
    void setManagement(const DataManager &management);
    Menu(DataManager& management);
    void start();

private:
    DataManager management;
    void printStudentInfo(const Student& student);
    bool areStringsEqualIgnoreCase(const std::string& str1, const std::string& str2);
    void consultarHorarios();
    void consultarHorarioAluno();
    void consultarHorarioTurma();
    void consultarHorarioUC();
    void consultarHorarioUCTurma();
    bool studentBelongsToUCAndClass(const Student& student, const string& ucCode, const string& classCode);
    void realizarAlteracoes();

    void consultarInformacoesUCs();
    void consultarInformacoesAlunos();
    void consultarNumEstudantesInscritosN_UC(int n);
    void consultarAlunosTurmaCursoAno();
    void consultarUcsComMaisEstudantes();

    void consultarTurmaAnoCursoUC();
    void  consultarTurmasUC();
    void consultarUcDeUmAno();
    void consultarUcComXOcupações();
    DataManager& management_;

    void consultarAlunosPorTurma();

    void consultarAlunosPorAno();

    bool isClassCodeValid(const string &input, const string &target) const;

    void displayClassSchedule(const ClassUC &uc) const;

    bool isStudentValid(const string &input, const Student &student) const;

    void displayStudentSchedule(const Student &student) const;

    bool correspondeCodigoUcETurma(const ClassUC &turma, const string &uccode, const string &classcode) const;

    void exibirHorarioDaTurma(const ClassUC &turma) const;
    void exibirHorarioDaUC(const ClassUC &turma) const;
    bool compararIgnorandoMaiusculas(const string &str1, const string &str2) const;

    bool correspondeCodigoUC(const ClassUC &turma, const string &ucCode) const;

    bool isNameOrUpValid(const string &input, const string &name, const string &upNumber) const;

    void displayClassHorario(const ClassUC &uc) const;

    void ingressarEmUC();

    void sairDeUC();

    void realizarAlteracoesTurma();
    void realizarAlteracoesUC();
};

#endif
