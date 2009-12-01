/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "mainwindow.h"

#include <KFileDialog>
#include <KStandardAction>
#include <KActionCollection>
#include <KAction>
#include <KDebug>
#include <KStatusBar>
#include <KMessageBox>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KPluginSelector>
#include <KRun>

#include <game.h>
#include <gameproject.h>

#include "lib/plugin.h"
#include "lib/pluginmanager.h"
#include "lib/objectmanager.h"

#include "gluoncreatorsettings.h"
#include "dialogs/configdialog.h"
#include "gamethread.h"

using namespace Gluon::Creator;

MainWindow::MainWindow() : KXmlGuiWindow()
{
    Gluon::GluonObjectFactory::instance()->loadPlugins();

    PluginManager::instance()->setParent(this);
    ObjectManager::instance()->setParent(this);

    setupGame();

    setDockNestingEnabled(true);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

    PluginManager::instance()->setMainWindow(this);
    PluginManager::instance()->loadPlugins();

    m_gameThread = new GameThread(this);

    setupActions();

    setupGUI();
}

MainWindow::~MainWindow()
{
    Gluon::Game::instance()->stopGame();
}

void MainWindow::newProject()
{
    KRun::run("gluoncreator", KUrl::List(), this);
}

void MainWindow::openProject()
{
    QString fileName = KFileDialog::getOpenFileName();
    openProject(fileName);
}

void MainWindow::openProject(const QString &fileName)
{
    statusBar()->showMessage(i18n("Opening project..."));
    if(!fileName.isEmpty()) {
        Gluon::GameProject* project = new Gluon::GameProject();
        project->loadFromFile(QUrl(fileName));

        Gluon::Game::instance()->setGameProject(project);
    }
    statusBar()->showMessage(i18n("Project successfully opened"));
}

void MainWindow::saveProject()
{
    saveProject(m_fileName);
}

void MainWindow::saveProject(const QString &fileName)
{
    if(!fileName.isEmpty())
    {
        statusBar()->showMessage(i18n("Saving project..."));
        Gluon::Game::instance()->gameProject()->setFilename(QUrl(fileName));
        if(!Gluon::Game::instance()->gameProject()->saveToFile())
        {
            KMessageBox::error(this, i18n("Could not save file."));
            return;
        }
        statusBar()->showMessage(i18n("Project successfully saved."));
    }
    else
    {
        saveProjectAs();
    }
}

void MainWindow::saveProjectAs()
{
    m_fileName = KFileDialog::getSaveFileName();
    if(!m_fileName.isEmpty()) saveProject();
}

void MainWindow::setupGame()
{
    Gluon::GameProject* project = new Gluon::GameProject(Gluon::Game::instance());
    project->setName(i18n("New Project"));
    Gluon::Game::instance()->setGameProject(project);

    Gluon::GameObject* root = ObjectManager::instance()->createNewScene();
    Gluon::Game::instance()->setCurrentScene(root);
}

void MainWindow::setupActions()
{
    KStandardAction::openNew(this, SLOT(newProject()), actionCollection());

    KAction* newObject = new KAction(KIcon("document-new"), i18n("New Object"), actionCollection());
    actionCollection()->addAction("newObject", newObject);
    connect(newObject, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewObject()));

    KAction* newScene = new KAction(KIcon("document-new"), i18n("New Scene"), actionCollection());
    actionCollection()->addAction("newScene", newScene);
    connect(newScene, SIGNAL(triggered(bool)), ObjectManager::instance(), SLOT(createNewScene()));

    KAction* play = new KAction(KIcon("media-playback-start"), i18n("Play Game"), actionCollection());
    actionCollection()->addAction("playGame", play);
    connect(play, SIGNAL(triggered(bool)), SLOT(startGame()));

    KAction* pause = new KAction(KIcon("media-playback-pause"), i18n("Pause Game"), actionCollection());
    actionCollection()->addAction("pauseGame", pause);
    pause->setCheckable(true);
    pause->setEnabled(false);
    connect(pause, SIGNAL(triggered(bool)), Gluon::Game::instance(), SLOT(setPause(bool)));

    KAction* stop = new KAction(KIcon("media-playback-stop"), i18n("Stop Game"), actionCollection());
    actionCollection()->addAction("stopGame", stop);
    stop->setEnabled(false);
    connect(stop, SIGNAL(triggered(bool)), SLOT(stopGame()));

    KStandardAction::open(this, SLOT(openProject()), actionCollection());
    KStandardAction::save(this, SLOT(saveProject()), actionCollection());
    KStandardAction::saveAs(this, SLOT(saveProjectAs()), actionCollection());
    KStandardAction::quit(this, SLOT(close()), actionCollection());
    KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());
}

void Gluon::Creator::MainWindow::showPreferences()
{
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }
    ConfigDialog *dialog = new ConfigDialog(this, "settings", Gluon::Settings::self());
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}

void Gluon::Creator::MainWindow::startGame()
{
    actionCollection()->action("playGame")->setEnabled(false);
    actionCollection()->action("pauseGame")->setEnabled(true);
    actionCollection()->action("stopGame")->setEnabled(true);
    m_gameThread->start();
}

void Gluon::Creator::MainWindow::stopGame()
{
    Game::instance()->stopGame();
    actionCollection()->action("playGame")->setEnabled(true);
    actionCollection()->action("pauseGame")->setEnabled(false);
    actionCollection()->action("pauseGame")->setChecked(false);
    actionCollection()->action("stopGame")->setEnabled(false);
}

