/*
 note_edit_view.h     MindForger thinking notebook

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
#ifndef M8R_NOTE_EDIT_VIEW_H
#define M8R_NOTE_EDIT_VIEW_H

#include <QtWidgets>

#include "note_editor_view.h"
#include "panels/edit_name_and_buttons_panel.h"

namespace m8r {

class NoteEditView : public QWidget
{
private:
    EditTitleAndButtonsPanel* editTitleAndButtonsPanel;
    NoteEditorView* noteEditor;

public:
    explicit NoteEditView(QWidget* parent);
    NoteEditView(const NoteEditView&) = delete;
    NoteEditView(const NoteEditView&&) = delete;
    NoteEditView &operator=(const NoteEditView&) = delete;
    NoteEditView &operator=(const NoteEditView&&) = delete;
    ~NoteEditView();

    void setNoteEditDialog(NoteEditDialog* noteEditDialog) { editTitleAndButtonsPanel->setNoteEditDialog(noteEditDialog); }

    void setNoteTitle(const std::string& name) { editTitleAndButtonsPanel->setTitle(name); }
    void setNoteDescription(std::string& description) { noteEditor->setPlainText(QString::fromStdString(description)); }
    QString getNoteDescription(void) const { return noteEditor->toPlainText(); }
    // IMPROVE toPlainText() to determine empty is expensive
    bool isNoteDescriptionEmpty(void) const { return noteEditor->toPlainText().isEmpty(); }
};

}
#endif // M8R_NOTE_EDIT_VIEW_H
