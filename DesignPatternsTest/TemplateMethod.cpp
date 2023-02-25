#include "util.h"

/**
 * @brief 职责链
 * 分类: 行为型(类)
 * 定义一个算法骨架，
 * 而将一些步骤延迟到子类。
 * 模板方法使得子类可以不改变一个算法的结构，
 * 即可重新定义该算法的某些特定步骤。
*/

class DataMiner
{
public:
    // template method
    void mineData(const string& path) {
        openFile(path);
        extracData();
        makeReport();
        hook1();
        closeFile();
    }
protected:
    virtual void openFile(const string& path) = 0;
    void extracData() const {
        cout << "DataMiner: 从字符串中提取相关数据。" << endl;
    }
    void makeReport() const {
        cout << "DataMiner: 生成数据分析报告。" << endl;
    }
    virtual void closeFile() const = 0;
    virtual void hook1() const {}
protected:
    string m_path;
};

class PDFDataMiner : public DataMiner
{
public:
    virtual void openFile(const string& path) override {
        m_path = "openFile(paht)";
        cout << "PDFDataMiner: 打开PDF文件，转换为字符串序列。" << endl;
    }
    virtual void closeFile() const override {
        cout << "PDFDataMiner: 关闭PDF文件。" << endl;
    }
};

class WordDataMiner : public DataMiner
{
public:
    virtual void openFile(const string& path) override {
        m_path = "openFile(paht)";
        cout << "WordDataMiner: 打开Word文件，转换为字符串序列。" << endl;
    }
    virtual void closeFile() const override {
        cout << "WordDataMiner: 关闭Word文件。" << endl;
    }

    virtual void hook1() const override {
        cout << "WordDataMiner: 给Word文件添加水印。" << endl;
    }
};

void clientCode(DataMiner* dataMiner, const string& path) {
    dataMiner->mineData(path);
}

void TestTemplateMethod() {
    PDFDataMiner pdf;
    clientCode(&pdf, "a.pdf");

    cout << endl;

    WordDataMiner word;
    clientCode(&word, "b.doc");
}

