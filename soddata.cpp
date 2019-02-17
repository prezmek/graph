
#include <iostream>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "soddata.h"

int SodData::AddNode(std::string category, std::string value)
{
    std::string name = category + "-" + value;
    size_t i;
    for(i = 0; i < nodes.size(); i++) {
        if(nodes[i].name == name)
            return i;
    }
    nodes.push_back(Node(name, category, value));
    return i;
}

void SodData::ReadFile(char* filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", "cannot open file");
        exit(1);
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if(fields.length() != 5) {
            QMessageBox::information(0, "error", "Incorrect file format");
            exit(1);
        }

        int no1 = AddNode(fields[0].toStdString(), fields[1].toStdString());
        int no2 = AddNode(fields[2].toStdString(), fields[3].toStdString());
        int weight = fields[4].toInt();
        edges.push_back(Edge(no1, no2, weight));
    }

    file.close();

    std::cout << "No of nodes: " << nodes.size() << std::endl;
    std::cout << "No of edges: " << edges.size() << std::endl;
}
