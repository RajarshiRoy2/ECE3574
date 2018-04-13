#include <QTest>
#include <QPlainTextEdit>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>

#include "virtual_machine_gui.hpp"

#include "test_config.hpp"

class VirtualMachineGUITest : public QObject {
  Q_OBJECT

private slots:

  void initTestCase();
  void test2();
  void test3();
  void test4();
  void test5();
  void test6();
  void test7();
  void test8();
  void test9();
  void test10();
  void test11();
private:

  VirtualMachineGUI widget;
};

// this section just verifies the object names and API
void VirtualMachineGUITest::initTestCase(){
	
		
		widget.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test00.asm"));

		auto textWidget = widget.findChild<QPlainTextEdit *>("text");
		QVERIFY2(textWidget, "Could not find QPLainText widget");

		auto registerViewWidget = widget.findChild<QTableView *>("registers");
		QVERIFY2(registerViewWidget, "Could not find QTableView widget for registers");

		auto memoryViewWidget = widget.findChild<QTableView *>("memory");
		QVERIFY2(memoryViewWidget, "Could not find QTableView widget for memory");

		auto statusViewWidget = widget.findChild<QLineEdit *>("status");
		QVERIFY2(statusViewWidget, "Could not find QLineEdit widget for status");

		auto stepButtonWidget = widget.findChild<QPushButton *>("step");
		QVERIFY2(stepButtonWidget, "Could not find QTableView widget for memory");

		auto stepButtonWidget2 = widget.findChild<QPushButton *>("run");
		QVERIFY2(stepButtonWidget2, "Could not find QTableView widget for memory");

		auto stepButtonWidget3 = widget.findChild<QPushButton *>("break");
		QVERIFY2(stepButtonWidget3, "Could not find QTableView widget for memory");
	

}

void VirtualMachineGUITest::test2()
{

	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test00.asm"));
	//qDebug("\nstd out!");
	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	//qDebug() << s;
	{ QVERIFY(h == "Ok"); }
}

void VirtualMachineGUITest::test3()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test01.asm"));
	widget2.handleButton();
	//qDebug("\nstd out!");
	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	auto memory = widget2.memory;
	auto memmodel = memory->model();

	// this fails
	QVERIFY(memmodel->data(memmodel->index(8, 1)).toString().startsWith("0x01"));
	//qDebug() << s;
	{ QVERIFY(h == "Ok"); }
}

void VirtualMachineGUITest::test4()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test21.asm"));
	widget2.handleButton();
	//qDebug("\nstd out!");
	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	{ QVERIFY(!(h == "Error: File does not exist...")); }
}

void VirtualMachineGUITest::test5()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test06.asm"));
	widget2.handleButton();
	widget2.handleButton();
	widget2.handleButton();

	QString s;
	s = widget2.status->text();
	string h = s.toStdString();

	{ QVERIFY(h == "Ok"); }
}

void VirtualMachineGUITest::test6()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test07.asm"));
	widget2.handleButton();
	widget2.handleButton();
	widget2.handleButton();

	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	int y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
}

void VirtualMachineGUITest::test7()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test07.asm"));
	widget2.handleButton();
	widget2.handleButton();
	widget2.handleButton();

	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	int y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
	auto stepButtonWidget = widget.findChild<QLabel *>("status2");
	QVERIFY2(stepButtonWidget, "Could not find QTstatus label");
}

void VirtualMachineGUITest::test8()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test08.asm"));
	widget2.handleButton();
	widget2.handleButton();
	widget2.handleButton();

	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	int y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
	int u=widget2.registers->columnAt(2);
	{ QVERIFY(u == 0); }
}

void VirtualMachineGUITest::test9()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test09.asm"));
	widget2.handleButton();
	widget2.handleButton();
	widget2.handleButton();
	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	int y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
}

void VirtualMachineGUITest::test10()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test10.asm"));
	widget2.handleButton();
	widget2.handleButton();
	widget2.handleButton();

	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	int y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
}
void VirtualMachineGUITest::test11()
{
	VirtualMachineGUI widget2;
	widget2.load(QString::fromStdString(TEST_FILE_DIR + "/vm/test10.asm"));
	widget2.handleButtonrun();

	widget2.handleButtonbreak();
	QString s;
	s = widget2.status->text();
	string h = s.toStdString();
	int y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
	widget2.handleButton();
	s = widget2.status->text();
	 h = s.toStdString();
	y = widget2.memory->columnWidth(0);
	{ QVERIFY(h == "Ok"); }
	{ QVERIFY(y == 100); }
}

QTEST_MAIN(VirtualMachineGUITest)
#include "virtual_machine_gui_test.moc"

