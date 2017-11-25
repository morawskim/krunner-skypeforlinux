#ifndef SKYPE_H
#define SKYPE_H

#include <KRunner/AbstractRunner>

class Skype : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    Skype(QObject *parent, const QVariantList &args);
    ~Skype();

    void match(Plasma::RunnerContext &);
    void run(const Plasma::RunnerContext &, const Plasma::QueryMatch &);
};

#endif
