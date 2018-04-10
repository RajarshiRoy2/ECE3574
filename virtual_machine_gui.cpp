#include "virtual_machine_gui.hpp"

using namespace std;

VirtualMachineGUI::VirtualMachineGUI(QWidget *parent) : QWidget(parent)
{
	text = new QPlainTextEdit();
	text->setObjectName("text");
	format2.setBackground(Qt::white);
	format.setBackground(Qt::yellow);
	text->setTextInteractionFlags(Qt::NoTextInteraction);


	registers = new QTableView;
	registers->setEditTriggers(QAbstractItemView::NoEditTriggers);
	registers->setObjectName("registers");
	registers->verticalHeader()->setVisible(false);
	QStandardItemModel *model = new QStandardItemModel(34, 3);
	model->setHeaderData(0, Qt::Horizontal, tr("Number"));
	model->setHeaderData(1, Qt::Horizontal, tr("Alias"));
	model->setHeaderData(2, Qt::Horizontal, tr("Value(Hex)"));
	registers->setModel(model);
	vector<string>alias{ "$pc","$hi","$lo","$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra" };
	for (int i = 0; i < alias.size(); i++)
	{
		QString qst = QString::fromStdString(alias.at(i));
		QStandardItem *item = new QStandardItem(qst);
		model->setItem(i, 1, item);
	}
	vector<string> v{ "$0","$1","$2","$3","$4","$5","$6","$7","$8","$9","$10","$11","$12","$13","$14","$15","$16","$17","$18","$19","$20","$21","$22","$23","$24","$25","$26","$27","$28","$29","$30","$31" };
	for (int i = 0; i <v.size(); i++)
	{
		stringstream stream;
		stream << "0x" << setw(8) << setfill('0') << hex << machine.registers[v.at(i)];
		string result(stream.str());
		QString qst1 = QString::fromStdString(result);
		QStandardItem *item1 = new QStandardItem(qst1);
		model->setItem(i + 3, 2, item1);

		QString qst = QString::fromStdString(v.at(i));
		QStandardItem *item = new QStandardItem(qst);
		model->setItem(i + 3, 0, item);

	}
	stringstream stream;
	stream << "0x" << setw(8) << setfill('0') << hex << machine.line2;
	string result(stream.str());
	QString qst1 = QString::fromStdString(result);
	QStandardItem *item1 = new QStandardItem(qst1);
	model->setItem(0, 2, item1);

	stringstream stream1;
	stream1 << "0x" << setw(8) << setfill('0') << hex << machine.hi;
	string result1(stream1.str());
	QString qst11 = QString::fromStdString(result1);
	item1 = new QStandardItem(qst11);
	model->setItem(1, 2, item1);

	stringstream stream2;
	stream2 << "0x" << setw(8) << setfill('0') << hex << machine.lo;
	string result2(stream2.str());
	QString qst12 = QString::fromStdString(result2);
	QStandardItem *item12 = new QStandardItem(qst12);
	model->setItem(2, 2, item12);

	memory = new QTableView;
	memory->setObjectName("memory");
	memory->verticalHeader()->setVisible(false);

	status = new QLineEdit;
	status->setReadOnly(true);
	status->setObjectName("status");
	status->setMinimumWidth(100);
	QLabel *label = new QLabel(QApplication::translate("nestedlayouts", "Status:"));
	label->setObjectName("status2");


	step = new QPushButton("Step", this);
	connect(step, SIGNAL(released()), this, SLOT(handleButton()));
	step->setObjectName("step");

	run = new QPushButton("Run", this);
	connect(run, SIGNAL(released()), this, SLOT(handleButtonrun()));
	run->setObjectName("run");
	break2 = new QPushButton("Break", this);
	connect(break2, SIGNAL(released()), this, SLOT(handleButtonbreak()));
	break2->setObjectName("break");
	break2->setEnabled(false);

	QHBoxLayout *queryLayout = new QHBoxLayout();
	queryLayout->addWidget(text);
	queryLayout->addWidget(registers);
	queryLayout->addWidget(memory);

	QHBoxLayout *mainLayout2 = new QHBoxLayout();
	mainLayout2->addWidget(label);
	mainLayout2->addWidget(status);

	QHBoxLayout *mainLayout3 = new QHBoxLayout();
	mainLayout3->addWidget(step);
	mainLayout3->addWidget(run);
	mainLayout3->addWidget(break2);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(queryLayout);
	mainLayout->addLayout(mainLayout2);
	mainLayout->addLayout(mainLayout3);
	setLayout(mainLayout);

}

VirtualMachineGUI::~VirtualMachineGUI()
{

}

bool is_file_exist(QString fileName)
{
	string str = fileName.toStdString();
	ifstream infile(str);
	return infile.good();
}

void VirtualMachineGUI::load(QString name)
{
	bool t = is_file_exist(name);
	if (t == false)
	{
		status->setText("Error: File does not exist...");
	}
	else
	{
		status->setText("Ok");
		fstream inFile;
		string str = name.toStdString();
		Parser parser;
		string value, input, sum;
		inFile.open(str);
		while (getline(inFile, input))
		{
			sum = sum + "\n" + input;
		}
		//	cout << sum << endl;

		inFile.close();
		qstr1 = QString::fromStdString(sum);
		text->setPlainText(qstr1);
		QString qstr2;
		if (!parser.tokens(sum)) //checking for error
		{
			qstr2 = QString::fromStdString(parser.my_error());
			status->setText(qstr2);
		}
		//	sum.clear();
		inFile.open(str);
		while (getline(inFile, input))
		{
			size_t found = input.find(".text");
			if (found > 0 && found != 4294967295)
			{

				break;
			}
			sum = sum + "\n" + input;
		}
		istringstream iss(sum);
		TokenList tl1 = tokenize(iss);

		machine.setting_data_values(tl1);
		sum.clear();
		while (getline(inFile, input))
		{
			if (input != ""&&input != " "&&input != "\t")
				sum = sum + "\n" + input;
		}

		//cout << sum << endl;
		string ty = sum;
		std::istringstream tokenStream(ty);
		while (std::getline(tokenStream, ty, '\n'))
		{
			tokens2.push_back(ty);
		}

		for (int i = 1; i < tokens2.size(); i++)
		{
			if (tokens2.at(i).back() == ':')
				tokens2.erase(tokens2.begin() + i);
		}

		istringstream iss1(sum);
		TokenList tl11 = tokenize(iss1);
		machine.saving_instr(tl11);
		inFile.close();

		QString qstr4 = QString::fromStdString(tokens2.at(1));
		u = text->find(qstr4, QTextDocument::FindCaseSensitively);
		//text->moveCursor(QTextCursor::Start);
		//text->textCursor().mergeCharFormat(format);

		QStandardItemModel *mode = new QStandardItemModel(512, 2);
		mode->setHeaderData(0, Qt::Horizontal, tr("Address(Hex)"));
		mode->setHeaderData(1, Qt::Horizontal, tr("Value(Hex)"));
		memory->setModel(mode);
		memory->setEditTriggers(QAbstractItemView::NoEditTriggers);
		for (int i = 0; i <512; i++)
		{
			stringstream stream3;
			stream3 << "0x" << setw(8) << setfill('0') << hex << i;
			string result3(stream3.str());
			QString qst123 = QString::fromStdString(result3);
			QStandardItem *item123 = new QStandardItem(qst123);
			mode->setItem(i, 0, item123);

			if ((int)machine.memory.at(i) < 15)
			{
				stringstream stream4;
				stream4 << "0x" // show the 0x prefix
					<< "0" << hex << (int)machine.memory.at(i) << endl;
				string result45(stream4.str());
				QString qs = QString::fromStdString(result45);
				QStandardItem *item45 = new QStandardItem(qs);
				mode->setItem(i, 1, item45);

			}
			else
			{
				stringstream stream4;
				stream4 << "0x" << internal << setfill('0') << hex << (int)machine.memory.at(i) << endl;
				string result45(stream4.str());
				QString qs = QString::fromStdString(result45);
				QStandardItem *item45 = new QStandardItem(qs);
				mode->setItem(i, 1, item45);

			}
		}
	}
}
void VirtualMachineGUI::handleButtonrun()
{
	if (machine.status.empty() && machine.line2 < machine.instructions.size())
	{
		run->setEnabled(false);
		step->setEnabled(false);
		break2->setEnabled(true);
		//VirtualMachineGUI * taskPtr = new VirtualMachineGUI(this);
		std::thread th(&VirtualMachineGUI::handleResults, this);
		th.detach();

	}
	else
	{
			status->setText("Error: Instructions finished");
	}

}
void VirtualMachineGUI::handleResults()
{
	
	while (machine.status.empty())
	{
		
		machine.executing_instr();
		if (machine.line2 >= machine.instructions.size())
		{
			status->setText("Error: Instructions finished");
			break;
		}
		if (vec.size() != 0)
		{
			break;
			vec.the_vec.clear();
		}
	}
	
}


void VirtualMachineGUI::findit()
{
	if (machine.line2 + 1 < machine.instructions.size())
	{
		QString qstr4 = QString::fromStdString(tokens2.at(machine.line2 + 1));
		u = text->find(qstr4, QTextDocument::FindCaseSensitively);
		if (u == false)
		{
			text->find(qstr4, QTextDocument::FindBackward);
		}
		//qDebug()<< qstr4;
	}
	else
	{
		QString qstr4 = QString::fromStdString(tokens2.at(machine.instructions.size()));
		u = text->find(qstr4, QTextDocument::FindCaseSensitively);
		if (u == false)
		{
			QString qstr4 = QString::fromStdString(tokens2.at(machine.line2));
			text->find(qstr4, QTextDocument::FindBackward);
		}
	}
}

void VirtualMachineGUI::handleButtonbreak()
{
	    
		run->setEnabled(true);
		step->setEnabled(true);
		break2->setEnabled(false);
		vec.append("break");
		findit();
		run2();

}

void VirtualMachineGUI::run2()
{
	
	QStandardItemModel *model = new QStandardItemModel(34, 3);
	model->setHeaderData(0, Qt::Horizontal, tr("Number"));
	model->setHeaderData(1, Qt::Horizontal, tr("Alias"));
	model->setHeaderData(2, Qt::Horizontal, tr("Value(Hex)"));
	registers->setModel(model);
	vector<string>alias{ "$pc","$hi","$lo","$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra" };
	for (int i = 0; i < alias.size(); i++)
	{
		QString qst = QString::fromStdString(alias.at(i));
		QStandardItem *item = new QStandardItem(qst);
		model->setItem(i, 1, item);
	}
	vector<string> v{ "$0","$1","$2","$3","$4","$5","$6","$7","$8","$9","$10","$11","$12","$13","$14","$15","$16","$17","$18","$19","$20","$21","$22","$23","$24","$25","$26","$27","$28","$29","$30","$31" };
	for (int i = 0; i < v.size(); i++)
	{
		stringstream stream;
		stream << "0x" << setw(8) << setfill('0') << hex << machine.registers[v.at(i)];
		string result(stream.str());
		QString qst1 = QString::fromStdString(result);
		QStandardItem *item1 = new QStandardItem(qst1);
		model->setItem(i + 3, 2, item1);

		QString qst = QString::fromStdString(v.at(i));
		QStandardItem *item = new QStandardItem(qst);
		model->setItem(i + 3, 0, item);

	}

	stringstream stream;
	stream << "0x" << setw(8) << setfill('0') << hex << machine.line2;
	string result(stream.str());
	QString qst1 = QString::fromStdString(result);
	QStandardItem *item1 = new QStandardItem(qst1);
	model->setItem(0, 2, item1);

	stringstream stream1;
	stream1 << "0x" << setw(8) << setfill('0') << hex << machine.hi;
	string result1(stream1.str());
	QString qst11 = QString::fromStdString(result1);
	item1 = new QStandardItem(qst11);
	model->setItem(1, 2, item1);

	stringstream stream2;
	stream2 << "0x" << setw(8) << setfill('0') << hex << machine.lo;
	string result2(stream2.str());
	QString qst12 = QString::fromStdString(result2);
	QStandardItem *item12 = new QStandardItem(qst12);
	model->setItem(2, 2, item12);

	QStandardItemModel *mode = new QStandardItemModel(512, 2);
	mode->setHeaderData(0, Qt::Horizontal, tr("Address(Hex)"));
	mode->setHeaderData(1, Qt::Horizontal, tr("Value(Hex)"));
	memory->setModel(mode);
	memory->setEditTriggers(QAbstractItemView::NoEditTriggers);
	for (int i = 0; i <512; i++)
	{
		stringstream stream3;
		stream3 << "0x" << setw(8) << setfill('0') << hex << i;
		string result3(stream3.str());
		QString qst123 = QString::fromStdString(result3);
		QStandardItem *item123 = new QStandardItem(qst123);
		mode->setItem(i, 0, item123);

		if ((int)machine.memory.at(i) < 15)
		{
			stringstream stream4;
			stream4 << "0x" << "0" << hex << (int)machine.memory.at(i) << endl;
			string result45(stream4.str());
			QString qs = QString::fromStdString(result45);
			QStandardItem *item45 = new QStandardItem(qs);
			mode->setItem(i, 1, item45);

		}
		else
		{
			stringstream stream4;
			stream4 << "0x" << internal << setfill('0') << hex << (int)machine.memory.at(i) << endl;
			string result45(stream4.str());
			QString qs = QString::fromStdString(result45);
			QStandardItem *item45 = new QStandardItem(qs);
			mode->setItem(i, 1, item45);

		}
	}
}

void VirtualMachineGUI::handleButton()
{
	if (machine.status.empty() && machine.line2 < machine.instructions.size())
	{
		machine.executing_instr();
		findit();
		run2();
	}
	else
	{
		status->setText("Error: Instructions finished");
	}
}
