#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow da inicio a programacao em qt
     * @param parent um ponteiro da classe QWidget
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public slots:
    /**
     * @brief putData um slot para capturar um certo dado(valor)
     */
    void putData();
    /**
     * @brief tcpDisconnect slot do botao para desconectar-se ao servidor
     */
    void tcpDisconnect();
    /**
     * @brief tcpConnect slot do botao para conectar-se ao servidor
     */
    void tcpConnect();
    /**
     * @brief on_start_clicked slot do botao para dar inicio ao capturar dados
     */
    void on_start_clicked();
    /**
     * @brief on_stop_clicked slot para parar a captura de dados
     */
    void on_stop_clicked();
    /**
     * @brief timerEvent um funçao dependente para controlar o tempo do programa
     * @param e um ponteiro da classe TimerEvent
     */
    void timerEvent(QTimerEvent *e);

private slots:

private:
    /**
     * @brief ui ponteiro da classe MainWindow que representa a caixa do programa
    */
    Ui::MainWindow *ui;
    /**
     * @brief socket um ponteiro da classe QTcpSocket que faz a ligacao com o servidor
     */
    QTcpSocket *socket;
    /**
     * @brief time um ponteiro time para armazenar o tempo
     */
    QTimer *time;
    /**
     * @brief id uma variavel double para guardar o indice da funcao startTimer()
     */
    double id;
    /**
     * @brief flag_click variavel para dizer se o botao start ja foi usado ou nao
     */
    int flag_click = 0;
};

#endif // MAINWINDOW_H
