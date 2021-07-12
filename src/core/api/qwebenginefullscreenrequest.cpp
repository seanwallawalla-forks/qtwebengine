/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qwebenginefullscreenrequest.h"

QT_BEGIN_NAMESPACE

/*!
    \class QWebEngineFullScreenRequest
    \brief The QWebEngineFullScreenRequest class enables accepting or rejecting
     requests for entering and exiting the fullscreen mode.

    \since 5.6

    \inmodule QtWebEngineCore

    To allow elements such as videos to be shown in the fullscreen mode,
    applications must set QWebEngineSettings::FullScreenSupportEnabled and
    connect to QWebEnginePage::fullScreenRequested, which takes a
    QWebEngineFullScreenRequest instance as an argument.

    If an element of a web page requests to be shown in the fullscreen mode,
    QWebEnginePage::fullScreenRequested will be emitted with an
    QWebEngineFullScreenRequest instance as an argument where toggleOn() returns
    \c true. The signal handler needs to then either call accept() or reject().

    If the request to enter the fullscreen mode is accepted, the element
    requesting fullscreen mode will fill the viewport, but it is up to the
    application to make the view fullscreen or to move the page to a view that
    is in the fullscreen mode.

    Likewise, a QWebEnginePage::fullScreenRequested will be emitted when
    the user wants to leave the full screen mode (that is, through the
    QWebEnginePage::ExitFullScreen context menu action). In this case,
    toggleOn() will return \c false, and the signal handler again needs to
    accept() or reject() the request. If it is accepted, the applicaton needs to
    make sure that the global window state is restored.
*/

/*!
    \property QWebEngineFullScreenRequest::toggleOn
    \brief Whether the web page has issued a request to enter fullscreen mode.
*/

/*!
    \property QWebEngineFullScreenRequest::origin
    \brief The URL to be opened in the fullscreen mode.
*/

/*
    Creates a request for opening the \a page from the URL specified by
    \a origin in the fullscreen mode if \a fullscreen is \c true.
*/

class QWebEngineFullScreenRequestPrivate : public QSharedData {
public:
    QWebEngineFullScreenRequestPrivate(const QUrl &origin, bool toggleOn, const std::function<void (bool)> &setFullScreenCallback)
        : m_origin(origin)
        , m_toggleOn(toggleOn)
        , m_setFullScreenCallback(setFullScreenCallback) { }

    const QUrl m_origin;
    const bool m_toggleOn;
    const std::function<void (bool)> m_setFullScreenCallback;
};

QWebEngineFullScreenRequest::QWebEngineFullScreenRequest(const QUrl &origin, bool toggleOn, const std::function<void (bool)> &setFullScreenCallback)
    : d_ptr(new QWebEngineFullScreenRequestPrivate(origin, toggleOn, setFullScreenCallback)) { }

QWebEngineFullScreenRequest::QWebEngineFullScreenRequest(const QWebEngineFullScreenRequest &other) = default;
QWebEngineFullScreenRequest& QWebEngineFullScreenRequest::operator=(const QWebEngineFullScreenRequest &other) = default;
QWebEngineFullScreenRequest::QWebEngineFullScreenRequest(QWebEngineFullScreenRequest &&other) = default;
QWebEngineFullScreenRequest& QWebEngineFullScreenRequest::operator=(QWebEngineFullScreenRequest &&other) = default;
QWebEngineFullScreenRequest::~QWebEngineFullScreenRequest() = default;

/*!
    Rejects a request to enter or exit the fullscreen mode.
*/
void QWebEngineFullScreenRequest::reject()
{
    d_ptr->m_setFullScreenCallback(!d_ptr->m_toggleOn);
}

/*!
    Accepts the request to enter or exit the fullscreen mode.
*/
void QWebEngineFullScreenRequest::accept()
{
    d_ptr->m_setFullScreenCallback(d_ptr->m_toggleOn);
}

/*!
    \fn QWebEngineFullScreenRequest::toggleOn() const
    Returns \c true if the web page has issued a request to enter the fullscreen
    mode, otherwise returns \c false.
*/
bool QWebEngineFullScreenRequest::toggleOn() const
{
    return d_ptr->m_toggleOn;
}

/*!
    \fn QWebEngineFullScreenRequest::origin() const
    Returns the URL to be opened in the fullscreen mode.
*/
QUrl QWebEngineFullScreenRequest::origin() const
{
    return d_ptr->m_origin;
}

QT_END_NAMESPACE
