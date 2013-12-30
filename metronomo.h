#ifndef METRONOMO_H
#define METRONOMO_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <ctime>
#include "botao.h"

class metronomo : public QWidget
{
    Q_OBJECT
public:
    metronomo(QWidget*);
    ~metronomo();
    float get_bpm();
    
signals:
    
public slots:
    void on_botao_pressed();
    void fechar();

private:
    QWidget *wid_metronomo, *filler, *parent;
    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout;
    Botao *botao;
    int rotacao;
    time_t tempo_ini, tempo_fin;
    float bpm;
    void calc_bpm();
};

#endif // METRONOMO_H
