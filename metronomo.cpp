#include "metronomo.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QWidget>

metronomo::metronomo(QWidget *parn) : QWidget(parn) {
    parent = parn;
    rotacao=0;

    wid_metronomo = new QWidget();
    wid_metronomo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    wid_metronomo->setFixedSize(300,300);
    wid_metronomo->setWindowTitle("Metrônomo");
    wid_metronomo->show();

    QLabel *text = new QLabel("Clique oito vezes no botão abaixo:", this);
    vlayout = new QVBoxLayout();
    hlayout = new QHBoxLayout();

    filler = new QWidget();
    filler->setMinimumSize(0,0);
    filler->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    botao = new Botao(this);
    botao->setFixedSize(70,70);
    botao->setIcon(QIcon(QPixmap(":/pics/clock1.png")));
    botao->setIconSize(QSize(40,40));
    botao->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    connect(botao,SIGNAL(pressed()),this,SLOT(on_botao_pressed()));

    hlayout->addWidget(filler);
    hlayout->addWidget(botao);
    hlayout->addWidget(filler);

    vlayout->addWidget(text);
    vlayout->addWidget(filler);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(filler);

    wid_metronomo->setLayout(vlayout);
    connect(this,SIGNAL(destroyed()),parent,SLOT(Adiciona_Botao_Metronomo()));
}

metronomo::~metronomo() {
    delete wid_metronomo;
    this->close();
}

void metronomo::on_botao_pressed() {
    switch(rotacao) {
        case 0: tempo_ini=time(NULL); rotacao++; break;
        case 1: botao->setIcon(QIcon(QPixmap(":/pics/clock2.png"))); rotacao++; break;
        case 2: rotacao++; break;
        case 3: botao->setIcon(QIcon(QPixmap(":/pics/clock3.png"))); rotacao++; break;
        case 4: rotacao++; break;
        case 5: botao->setIcon(QIcon(QPixmap(":/pics/clock4.png"))); rotacao++; break;
        case 6: rotacao++; break;
        case 7: tempo_fin=time(NULL); botao->setIcon(QIcon(QPixmap(":/pics/clock1.png"))); rotacao=0; calc_bpm(); break;
    }
}

void metronomo::calc_bpm() {
    bpm = 1.0*(difftime(tempo_fin,tempo_ini));
    QMessageBox *result_bpm = new QMessageBox();
    result_bpm->setWindowTitle("Frequência");

    if (bpm==0) {
        result_bpm->setText("ERRO!");
        result_bpm->setInformativeText("O Metrônomo não conseguiu identificar a frequência da batida.");
        result_bpm->exec();
    } else {
        bpm = 480.0/bpm;
        result_bpm->setText("O Metrônomo retorna uma batida de " + QString::number(bpm) + " bpm.");
        result_bpm->exec();
    }

    this->fechar();
}

void metronomo::fechar() {
    this->close();
}

float metronomo::get_bpm() {
    return bpm;
}