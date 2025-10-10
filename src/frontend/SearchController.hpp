#pragma once

#include <QObject>

#include <backends/BackendController.hpp>

class SearchController : public QObject
{
    Q_OBJECT
public:
    static SearchController* instance() {
        static SearchController sc;
        return &sc;
    }

    SearchController();

    static void registerType();

public slots:
    void search(const QString& query);
    void open(const QString& filePath);
    void copy(const QString& filePath);

signals:
    void clear();
    void searchFinished(Where::BackendController::Files);
    void error();

private:
    Where::BackendController backend;
};

