/*
    /kabuki_toolkit/gui/messagedialog.h -- Simple "OK" or "Yes/No"-style modal
   dialogs

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once
#include <pch.h>

#include "t_button.h"
#include "t_label.h"
#include "t_layout.h"
#include "t_window.h"

namespace _ {

/*
 * \class MessageDialog messagedialog.h /kabuki_toolkit/gui/messagedialog.h
 *
 * @brief Simple "OK" or "Yes/No"-style modal dialogs.
 */
class SDK MessageDialog : public Window {
 public:
  // Classification of the type of message this MessageDialog represents.
  enum class Type { Information, Question, Warning };

  MessageDialog(Widget *parent, Type type,
                const std::string &title = "Untitled",
                const std::string &message = "Message",
                const std::string &buttonText = "OK",
                const std::string &altButtonText = "Cancel",
                bool altButton = false)
      : Window(parent, title) {
    setLayout(new BoxLayout(Orientation::Vertical, Alignment::Middle, 10, 10));
    setModal(true);

    Widget *panel1 = new Widget(this);
    panel1->setLayout(
        new BoxLayout(Orientation::Horizontal, Alignment::Middle, 10, 15));
    int icon = 0;
    switch (type) {
      case Type::Information:
        icon = mTheme->mMessageInformationIcon;
        break;
      case Type::Question:
        icon = mTheme->mMessageQuestionIcon;
        break;
      case Type::Warning:
        icon = mTheme->mMessageWarningIcon;
        break;
    }
    Label *iconLabel =
        new Label(panel1, std::string(utf8(icon).data()), "icons");
    iconLabel->setFontSize(50);
    mMessageLabel = new Label(panel1, message);
    mMessageLabel->setFixedWidth(200);
    Widget *panel2 = new Widget(this);
    panel2->setLayout(
        new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 15));

    if (altButton) {
      Button *button =
          new Button(panel2, altButtonText, mTheme->mMessageAltButtonIcon);
      button->setCallback([&] {
        if (mCallback) mCallback(1);
        dispose();
      });
    }
    Button *button =
        new Button(panel2, buttonText, mTheme->mMessagePrimaryButtonIcon);
    button->setCallback([&] {
      if (mCallback) mCallback(0);
      dispose();
    });
    center();
    requestFocus();
  }

  Label *messageLabel() { return mMessageLabel; }
  const Label *messageLabel() const { return mMessageLabel; }

  std::function<void(int)> callback() const { return mCallback; }
  void setCallback(const std::function<void(int)> &callback) {
    mCallback = callback;
  }

 protected:
  std::function<void(int)> mCallback;
  Label *mMessageLabel;

 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace _
