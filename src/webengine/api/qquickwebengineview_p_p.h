/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef QQUICKWEBENGINEVIEW_P_P_H
#define QQUICKWEBENGINEVIEW_P_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qquickwebengineview_p.h"
#include "web_contents_adapter_client.h"

#include <QPointer>
#include <QScopedPointer>
#include <QSharedData>
#include <QString>
#include <QtCore/qcompilerdetection.h>
#include <QtGui/qaccessibleobject.h>

namespace QtWebEngineCore {
class WebContentsAdapter;
class UIDelegatesManager;
}

QT_BEGIN_NAMESPACE
class QQuickWebEngineView;
class QQmlComponent;
class QQmlContext;
class QQuickWebEngineContextMenuRequest;
class QQuickWebEngineSettings;
class QQuickWebEngineFaviconProvider;

QQuickWebEngineView::WebAction editorActionForKeyEvent(QKeyEvent* event);

#ifdef ENABLE_QML_TESTSUPPORT_API
class QQuickWebEngineTestSupport;
#endif

class Q_WEBENGINE_PRIVATE_EXPORT QQuickWebEngineViewPrivate : public QtWebEngineCore::WebContentsAdapterClient
{
public:
    Q_DECLARE_PUBLIC(QQuickWebEngineView)
    QQuickWebEngineView *q_ptr;
    QQuickWebEngineViewPrivate();
    ~QQuickWebEngineViewPrivate();

    QtWebEngineCore::UIDelegatesManager *ui();

    QtWebEngineCore::RenderWidgetHostViewQtDelegate* CreateRenderWidgetHostViewQtDelegate(QtWebEngineCore::RenderWidgetHostViewQtDelegateClient *client) override;
    QtWebEngineCore::RenderWidgetHostViewQtDelegate* CreateRenderWidgetHostViewQtDelegateForPopup(QtWebEngineCore::RenderWidgetHostViewQtDelegateClient *client) override;
    void titleChanged(const QString&) override;
    void urlChanged(const QUrl&) override;
    void iconChanged(const QUrl&) override;
    void loadProgressChanged(int progress) override;
    void didUpdateTargetURL(const QUrl&) override;
    void selectionChanged() override { }
    void recentlyAudibleChanged(bool recentlyAudible) override;
    QRectF viewportRect() const override;
    qreal dpiScale() const override;
    QColor backgroundColor() const override;
    void loadStarted(const QUrl &provisionalUrl, bool isErrorPage = false) override;
    void loadCommitted() override;
    void loadVisuallyCommitted() override;
    void loadFinished(bool success, const QUrl &url, bool isErrorPage = false, int errorCode = 0, const QString &errorDescription = QString()) override;
    void focusContainer() override;
    void unhandledKeyEvent(QKeyEvent *event) override;
    void adoptNewWindow(QSharedPointer<QtWebEngineCore::WebContentsAdapter> newWebContents, WindowOpenDisposition disposition, bool userGesture, const QRect &, const QUrl &targetUrl) override;
    bool isBeingAdopted() override;
    void close() override;
    void windowCloseRejected() override;
    void requestFullScreenMode(const QUrl &origin, bool fullscreen) override;
    bool isFullScreenMode() const override;
    void contextMenuRequested(const QtWebEngineCore::WebEngineContextMenuData &) override;
    void navigationRequested(int navigationType, const QUrl &url, int &navigationRequestAction, bool isMainFrame) override;
    void javascriptDialog(QSharedPointer<QtWebEngineCore::JavaScriptDialogController>) override;
    void runFileChooser(QSharedPointer<QtWebEngineCore::FilePickerController>) override;
    void showColorDialog(QSharedPointer<QtWebEngineCore::ColorChooserController>) override;
    void didRunJavaScript(quint64, const QVariant&) override;
    void didFetchDocumentMarkup(quint64, const QString&) override { }
    void didFetchDocumentInnerText(quint64, const QString&) override { }
    void didFindText(quint64, int) override;
    void didPrintPage(quint64 requestId, const QByteArray &result) override;
    void didPrintPageToPdf(const QString &filePath, bool success) override;
    void passOnFocus(bool reverse) override;
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString& message, int lineNumber, const QString& sourceID) override;
    void authenticationRequired(QSharedPointer<QtWebEngineCore::AuthenticationDialogController>) override;
    void runMediaAccessPermissionRequest(const QUrl &securityOrigin, MediaRequestFlags requestFlags) override;
    void runMouseLockPermissionRequest(const QUrl &securityOrigin) override;
    void runQuotaPermissionRequest(QSharedPointer<QtWebEngineCore::QuotaPermissionController>) override;
    QObject *accessibilityParentObject() override;
    QtWebEngineCore::WebEngineSettings *webEngineSettings() const override;
    void allowCertificateError(const QSharedPointer<CertificateErrorController> &errorController) override;
    void runGeolocationPermissionRequest(QUrl const&) override;
    void showValidationMessage(const QRect &anchor, const QString &mainText, const QString &subText) override;
    void hideValidationMessage() override;
    void moveValidationMessage(const QRect &anchor) override;
    void renderProcessTerminated(RenderProcessTerminationStatus terminationStatus, int exitCode) override;
    void requestGeometryChange(const QRect &geometry, const QRect &frameGeometry) override;
    void updateScrollPosition(const QPointF &position) override;
    void updateContentsSize(const QSizeF &size) override;
    void startDragging(const content::DropData &dropData, Qt::DropActions allowedActions,
                       const QPixmap &pixmap, const QPoint &offset) override;
    bool isEnabled() const override;
    void setToolTip(const QString &toolTipText) override;
    const QObject *holdingQObject() const override;

    QSharedPointer<QtWebEngineCore::BrowserContextAdapter> browserContextAdapter() override;
    QtWebEngineCore::WebContentsAdapter *webContentsAdapter() override;

    void setDevicePixelRatio(qreal);
    void adoptWebContents(QtWebEngineCore::WebContentsAdapter *webContents);
    void setProfile(QQuickWebEngineProfile *profile);
    void ensureContentsAdapter();
    void setFullScreenMode(bool);

    // QQmlListPropertyHelpers
    static void userScripts_append(QQmlListProperty<QQuickWebEngineScript> *p, QQuickWebEngineScript *script);
    static int userScripts_count(QQmlListProperty<QQuickWebEngineScript> *p);
    static QQuickWebEngineScript *userScripts_at(QQmlListProperty<QQuickWebEngineScript> *p, int idx);
    static void userScripts_clear(QQmlListProperty<QQuickWebEngineScript> *p);

    QSharedPointer<QtWebEngineCore::WebContentsAdapter> adapter;
    QScopedPointer<QQuickWebEngineHistory> m_history;
    QQuickWebEngineProfile *m_profile;
    QScopedPointer<QQuickWebEngineSettings> m_settings;
#ifdef ENABLE_QML_TESTSUPPORT_API
    QQuickWebEngineTestSupport *m_testSupport;
#endif
    QQmlComponent *contextMenuExtraItems;
    QtWebEngineCore::WebEngineContextMenuData m_contextMenuData;
    QUrl explicitUrl;
    QUrl iconUrl;
    QQuickWebEngineFaviconProvider *faviconProvider;
    int loadProgress;
    bool m_fullscreenMode;
    bool isLoading;
    bool m_activeFocusOnPress;
    bool m_navigationActionTriggered;
    bool m_validationShowing;
    qreal devicePixelRatio;
    QMap<quint64, QJSValue> m_callbacks;
    QList<QSharedPointer<CertificateErrorController> > m_certificateErrorControllers;
    QQmlWebChannel *m_webChannel;
    QPointer<QQuickWebEngineView> inspectedView;
    QPointer<QQuickWebEngineView> devToolsView;
    uint m_webChannelWorld;

private:
    QScopedPointer<QtWebEngineCore::UIDelegatesManager> m_uIDelegatesManager;
    QList<QQuickWebEngineScript *> m_userScripts;
    qreal m_dpiScale;
    QColor m_backgroundColor;
    qreal m_defaultZoomFactor;
    bool m_ui2Enabled;
};

#ifndef QT_NO_ACCESSIBILITY
class QQuickWebEngineViewAccessible : public QAccessibleObject
{
public:
    QQuickWebEngineViewAccessible(QQuickWebEngineView *o);
    QAccessibleInterface *parent() const override;
    int childCount() const override;
    QAccessibleInterface *child(int index) const override;
    int indexOfChild(const QAccessibleInterface*) const override;
    QString text(QAccessible::Text) const override;
    QAccessible::Role role() const override;
    QAccessible::State state() const override;

private:
    QQuickWebEngineView *engineView() const { return static_cast<QQuickWebEngineView*>(object()); }
};
#endif // QT_NO_ACCESSIBILITY
QT_END_NAMESPACE

#endif // QQUICKWEBENGINEVIEW_P_P_H
