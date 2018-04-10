#ifndef VIRTUAL_MACHINE_GUI_HPP
#define VIRTUAL_MACHINE_GUI_HPP
#include <QTimer>
#include <QString>
#include <QWidget>
#include <QThread>
#include <QFuture>
#include <QTextBlock>
#include <string>
#include <QPlainTextEdit>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include "VirtualMachine.hpp"
#include <iomanip>
#include <iostream>
#include "vector.hpp"
#include <fstream>
#include "parser.hpp"
#include <QTextDocument>
#include <QGraphicsTextItem>
#include <QLabel>
#include "lexer.hpp"
#include <QHeaderView>
#include <sstream>
#include <QLayout>
#include <QApplication>
#include <QStandardItemModel>
#include <QCoreApplication>
#include <QTextCharFormat>
#include <QTextFormat>
#include <QTextCursor>
#include <QDebug>
#include <algorithm>
#include<thread>

using namespace std;
class VirtualMachineGUI: public QWidget
{
	Q_OBJECT

public:
	VirtualMachineGUI(QWidget * parent = nullptr);

	~VirtualMachineGUI();
	void load(QString name);
	QPlainTextEdit* text;// widget with object name "text"
	QTableView * registers;// widget with object name "registers"
	QTableView * memory;// widget with object name "memory"
	QLineEdit * status;// widget with object name "status"
	QPushButton * step;// widget with object name "step"
	QPushButton * run;
	QPushButton * break2;
	VirtualMachine machine;
	void handleResults();
	
	QString qstr1;
	public slots:
	 void handleButton();
	 void handleButtonrun();
	 void handleButtonbreak();
	
private:
	std::thread * r;
	void findit();
	void run2();
	OutputVector<string> vec;
	QTextCursor cursor;
	QTextCharFormat format;
	QTextCharFormat format2;
	vector<string> tokens2;
	bool u;
	int pc;
	vector<int>line;
	
	QTextBlockFormat f;
	int y = 0;
	QList<QTextEdit::ExtraSelection> extraSelections;
	QTextEdit::ExtraSelection selection;

};
#endif
