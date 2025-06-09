
#include "inputmethod.h"
#include <QDebug>
#include <cstring>

static void registryHandler(void* data, wl_registry* registry,
                            uint32_t name, const char* interface, uint32_t version)
{
    InputMethod* self = static_cast<InputMethod*>(data);
    if (strcmp(interface, zwp_input_method_v1_interface.name) == 0) {
        self->input_method = static_cast<zwp_input_method_v1*>(
            wl_registry_bind(registry, name, &zwp_input_method_v1_interface, 1));
        static const zwp_input_method_v1_listener im_listener = {
            .activate = InputMethod::handleActivate,
            .deactivate = nullptr,
        };
        zwp_input_method_v1_add_listener(self->input_method, &im_listener, self);
        qDebug() << "Bound input_method";
    }
}

static void registryRemover(void*, wl_registry*, uint32_t) {}

InputMethod::InputMethod(wl_display* display)
{
    registry = wl_display_get_registry(display);
    static const wl_registry_listener registryListener = {
        registryHandler,
        registryRemover
    };
    wl_registry_add_listener(registry, &registryListener, this);
    wl_display_roundtrip(display);
}

void InputMethod::handleActivate(void* data,
                                 zwp_input_method_v1*,
                                 zwp_input_method_context_v1* ctx)
{
    InputMethod* self = static_cast<InputMethod*>(data);
    qDebug() << "Activated input method";
    self->context = ctx;
    self->serial++;
}

void InputMethod::sendText(const QString& text)
{
    if (!context) {
        qWarning() << "Cannot send text: context is null!";
        return;
    }
    QByteArray utf8 = text.toUtf8();
    zwp_input_method_context_v1_commit_string(context, serial, utf8.constData());
    zwp_input_method_context_v1_commit_state(context, serial++);
}
