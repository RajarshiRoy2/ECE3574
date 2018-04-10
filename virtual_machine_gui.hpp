#ifndef VIRTUAL_MACHINE_GUI_HPP
#define VIRTUAL_MACHINE_GUI_HPP

#include <QString>
#include <QWidget>
#include <string>
#include <QPlainTextEdit>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include "VirtualMachine.hpp"
#include <iomanip>
#include <iostream>
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
	VirtualMachine machine;
	QString qstr1;
	public slots:
	void handleButton();
private:
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
