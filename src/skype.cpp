#include <iostream>

#include <KLocalizedString>
#include <KConfigCore/KConfig>
#include <KConfigCore/KConfigGroup>

#include <QApplication>
#include <QProcess>
#include <QFileInfo>
#include <QDir>

#include "skype.h"

using namespace std;

Skype::Skype(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);
    
    // General runner configuration
    setObjectName(QLatin1String("Skype"));
    setHasRunOptions(true);
    setIgnoredTypes(Plasma::RunnerContext::Directory |
                    Plasma::RunnerContext::File |
                    Plasma::RunnerContext::NetworkLocation);
    setSpeed(AbstractRunner::NormalSpeed);
    setPriority(HighestPriority);
    setDefaultSyntax(
        Plasma::RunnerSyntax(
            QString::fromLatin1(":q:"),
            i18n("Opens a chat window with this user")
        )
    );
}

Skype::~Skype() {}

void Skype::match(Plasma::RunnerContext &context)
{
    if (!context.isValid()) return;

    QString home = QDir::homePath();
    QString path = home.append("/.local/skype.contacts");

    QFileInfo checkFile(path);
    if (!checkFile.exists() || !checkFile.isFile()) {
        return;
    }

    QString query = context.query();
    bool isQueryPrefixed = false;
    if (query.startsWith("skype")) {
            query = query.right(query.length() - 5).trimmed();
	    isQueryPrefixed = true;
    }

    QList<Plasma::QueryMatch> matches;

    QProcess ls;
    ls.start("cat", QStringList() << path);
    ls.waitForFinished();

    while (ls.canReadLine()) {
        QString line = QString::fromLocal8Bit(ls.readLine());
        line = line.trimmed();
        if (line.isEmpty()) {
            continue;
        }
        QStringList chunks = line.split(';');
        QString sessionName = chunks.first();
        QString skypeId = chunks.last();
        
        if (sessionName.contains(query, Qt::CaseInsensitive)) {
            // We have a match
            Plasma::QueryMatch match(this);
            // Basic properties for the match
            match.setIcon(QIcon::fromTheme("skypeforlinux"));
            match.setText(sessionName);
            match.setSubtext(i18n("Open chat with this user"));
            match.setData(skypeId);
            match.setId(skypeId);
	    float relevance = (float) query.length() / (float) sessionName.length();
            match.setRelevance(isQueryPrefixed ? 1.0 : relevance);
            matches.append(match);
        }
    }

    context.addMatches(matches);
}

void Skype::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);

    QString program("xdg-open");
    QString url("skype:");
    url.append(match.data().toString());
    url.append("?chat");

    QStringList args;
    args.append(url);

    QProcess::startDetached(program, args);
}

K_EXPORT_PLASMA_RUNNER(skype, Skype)

#include "skype.moc"
