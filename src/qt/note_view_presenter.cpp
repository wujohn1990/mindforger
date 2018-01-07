/*
 note_view_presenter.cpp     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "note_view_presenter.h"

#include "look_n_feel.h"

using namespace std;

namespace m8r {

NoteViewPresenter::NoteViewPresenter(NoteView* view, OrlojPresenter* orloj)
{
    this->view = view;    
    this->orloj = orloj;
    this->model = new NoteViewModel();
    this->view->setModel(this->model);

    this->markdownRepresentation
        = new MarkdownOutlineRepresentation{orloj->getMind()->ontology()};
    this->htmlRepresentation
        = new HtmlOutlineRepresentation{orloj->getMind()->ontology()};

    QObject::connect(
        view, SIGNAL(signalMouseDoubleClickEvent()),
        this, SLOT(slotEditNote()));
    QObject::connect(
        view, SIGNAL(signalFromViewNoteToOutlines()),
        orloj, SLOT(slotShowOutlines()));

}

// when HTML will be here: first decorate MD with HTML colors > then MD to HTML conversion
void NoteViewPresenter::refresh(Note* note, const QString* ftsExpr2Highlight)
{
    this->currentNote = note;

    // IMPROVE NPE
    QString noteHtml = QString::fromStdString(*htmlRepresentation->to(note));

    // TODO HtmlBuilderClass
    QString html("<html><body style='color: ");
    html += LookAndFeels::getInstance().getTextColor();
    html += QString::fromUtf8("'><pre>");

    if(ftsExpr2Highlight != nullptr) {
        QString highlighted = QString::fromStdString("<span style='background-color: red; color: white;'>");
        highlighted += ftsExpr2Highlight;
        highlighted += QString::fromStdString("</span>");
        noteHtml.replace(*ftsExpr2Highlight, highlighted);
    }
    html += noteHtml;
    html += QString::fromStdString("</pre></body></html>");

    view->setHtml(html);
}

void NoteViewPresenter::slotEditNote(void)
{
    string* md = markdownRepresentation->to(this->currentNote);
    orloj->showFacetNoteEdit(this->currentNote, md);
    // IMPROVE MD is leak
}

NoteViewPresenter::~NoteViewPresenter()
{
    if(markdownRepresentation) delete markdownRepresentation;
    if(htmlRepresentation) delete htmlRepresentation;
}

}