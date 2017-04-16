#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //3ICE: Recalculate if any of these three fields change:
    connect(ui->weight,SIGNAL(valueChanged(int)),this,SLOT(work()));
    connect(ui->height,SIGNAL(valueChanged(int)),this,SLOT(work()));
    //Female changes together with male, so I only need it once
    connect(ui->actionFemale,SIGNAL(changed()),this,SLOT(work()));
    //Interestingly, male only doesn't work, but female only does... WONTFIX

    //3ICE: You don't know my pain...
    //connect(ui->actionFemale,SIGNAL(changed()),this,SLOT(avoidInfiniteLoop()));

    //3ICE: Yeah, so GUI-created signals are terrible. Must use code.
    //Creative function names: f... m... l?
    connect(ui->actionFemale,SIGNAL(triggered(bool)),this,SLOT(f(bool)));
    connect(ui->actionMale,SIGNAL(triggered(bool)),this,SLOT(m(bool)));

    connect(ui->actionReset,SIGNAL(triggered(bool)),this,SLOT(reset()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::reset(){
    ui->height->setValue(0);
    ui->weight2->setValue(0);
    if(ui->actionMale->isChecked()){
        //3ICE: For some reason signals don't listen when unchecking:
        ui->actionMale->setChecked(false);
        //3ICE: so I have to toggle both. Strange...
        ui->actionFemale->setChecked(true);
        //I deleted most of the code that was responsible for the
        //above complained-about bug. (Not even commented out, just
        //straight up deleted...)
        //3ICE: This line used to be unnecessary:
        ui->gender->setText("Female");
        //3ICE: But I stopped listening for changed() signals.
    }
}

/** Who wants a docstring? I usually do it. But it's 5 am now... */
void MainWindow::work(){
    if(ui->height->value()==0.0 || ui->weight->value()==0.0){
        ui->interp->setText("-");
        ui->bmi->setText("-");
        return;
    }

    float m = (float)ui->height->value() / 100;
    float bmi = ui->weight->value() / (m*m);

    //ui->bmi->setText(to_string(bmi));
    //3ICE: Obviously to_string has been bugged for years now.
    //And even if _I_ fix it locally, _YOU_ still won't be able
    //to test & grade my code with your unpatched compiler.

    //Stringstream workaround (remember to include it):
    //std::ostringstream ss;ss<<bmi;std::string bmi_s(ss.str());
    //3ICE: Oh you expletive Qt... Won't even accept string, wants QString.

    //Well, here you go then, eat your QString:
    QString bmi_s = QString::number(bmi);
    ui->bmi->setText(bmi_s);

    //3ICE: Oops, could have used ui->bmi->setNum(bmi); //oh well...

    QString result;
    if(ui->actionFemale->isChecked()){
        if     (bmi<=19.1) result="Underweight";
        else if(bmi<=25.8) result="Normal";
        else if(bmi<=27.3) result="Slight overweight";
        else if(bmi<=32.2) result="Overweight";
        else               result="Much overweight";
    }else{
        if     (bmi<=20.7) result="Underweight";
        else if(bmi<=26.4) result="Normal";
        else if(bmi<=27.8) result="Slight overweight";
        else if(bmi<=31.1) result="Overweight";
        else               result="Much overweight";
    }

    ui->interp->setText(result);
}

//3ICE: I'm keeping this name because that's what the function did initially.
void MainWindow::avoidInfiniteLoop(){
    //3ICE: Let's start with a funny debug message I left in:
    //ui->bmi->setText(infiniteLoop?"1 dis fe, en ma":"0 dis ma en fe");

    //3ICE: Qt's signal editor sucks.
    //I tried my best to use the GUI, but it's sorely lacking.
    //Can't open menus while Signal editor is on.
    //Menus close as soon as you enter signal editing
    //And if you use the tiny green + icon, the editor doesn't open.
    //Only four basic dropdowns. No inherited signals, no adding new signals.
    //Writing it in code is far easier than struggling with that limited system.

    //I did force the signal editor to work for menu actions.
    //End result looks funny, the arrows are coming out of nowhere :)
    //But all that hacking did for me is waste my time, in the end...
    //female.triggered->male.toggle via GUI
    //male.triggered->female.toggle via GUI
    //3ICE: The above logic works for spinners (changed->setValue),
    //but crashes the app (!?) for radio checkboxes (triggered->toggle)

    //3ICE: I spent an hour playing with setEnabled, setDisabled here.
    //Almost perfect.

    //3ICE: Another hour with blockSignals(false), blockSignals(true)...
    //Everything good, except it breaks on Reset.

    //3ICE: Another hour on forcing the GUI editor to add a QActionGroup component
    //Then I could have used setExclusive(true) on it. But no matter what I did...
    //The sample app behaves differently from everything I tried. In minor ways.

    //Here's my worst workaround:
    //if(!ui->actionFemale->isChecked()){
    //    ui->actionMale->blockSignals(true);
    //    ui->actionFemale->blockSignals(false);
    ////or
    //    ui->actionFemale->setEnabled(true);
    //    ui->actionMale->setEnabled(false);
    ////or
    //    ui->actionFemale->setChecked(true);
    //    ui->actionMale->setChecked(false);
    //}else{
    //    ui->actionFemale->setChecked(false);
    //    ui->actionMale->setChecked(true);
    ////or
    //    ui->actionFemale->blockSignals(true);
    //    ui->actionMale->blockSignals(false);
    ////or
    //    ui->actionFemale->setDisabled(false);
    //    ui->actionMale->setDisabled(true);
    //}

    //3ICE: The only line of code that's still useful after my all-nighter:
    //3ICE: I love conditional operators (?:)
    //ui->gender->setText(ui->actionFemale->isChecked()?"Female":"Male");
    //Update: And now even that's broken. See f and m below for fix:
}

void MainWindow::f(bool on){
    if(on) ui->actionMale->setChecked(false);
    else ui->actionFemale->setChecked(true); //3ICE: Stop them from toggling it off
    ui->gender->setText("Female");
}

void MainWindow::m(bool on){
    if(on) ui->actionFemale->setChecked(false);
    else ui->actionMale->setChecked(true);
    ui->gender->setText("Male");
}
