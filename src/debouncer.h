/***************************************************************************
 *   copyright       : (C) 2025 by Kevin Exton <kevin.exton@pm.me>         *
 ***************************************************************************/
#pragma once
#ifndef Header_Debouncer
#define Header_Debouncer

#include <QObject>
#include <QPointer>
#include <QTimer>
#include <QVariant>
#include <cassert>
#include <memory>
#include <mutex>

namespace detail {
    /*!
     * \class Debouncer
     * \brief Manages the state and logic for debouncing a function call.
     * \ingroup detail
     *
     * The Debouncer class encapsulates the core mechanism for delaying a function
     * execution until a certain period of inactivity has passed. It owns the
     * QTimer, the function to be executed, and the connection management logic,
     * ensuring thread-safe operation.
     *
     * This class is designed to be move-only, as it uniquely manages the
     * underlying timer and Qt connection resources. It is not intended for direct
     * use, but rather as the implementation detail captured by the lambda returned
     * from the `debounce()` factory function.
     *
     * Its lifetime is tied to the object that holds the returned callable from
     * `debounce()`. When that callable is destroyed, this Debouncer instances
     * also destroyed, safely cleaning up the timer and connection.
     *
     * \tparam Func The type of the callable (e.g., function pointer, lambda)
     * that will be debounced.
     */
    template <typename Func>
    class Debouncer {
    public:
        Debouncer() noexcept
            : m_context{nullptr},
            m_timer{nullptr},
            m_connection{std::make_unique<QMetaObject::Connection>()}
        {}

        Debouncer(Func&& func, QObject *context, int durationMs)
            : m_context(context),
            m_func(std::make_unique<std::decay_t<Func>>(std::forward<Func>(func))),
            m_timer(new QTimer(context)),
            m_connection(std::make_unique<QMetaObject::Connection>())
        {
            m_timer->setInterval(durationMs);
            m_timer->setSingleShot(true);
        }

        Debouncer(const Debouncer&) = delete;
        Debouncer& operator=(const Debouncer&) = delete;

        Debouncer(Debouncer&& other) noexcept
            : Debouncer()
        {
            swap(*this, other);
        }

        Debouncer& operator=(Debouncer&& other) noexcept {
            swap(*this, other);
            return *this;
        }

        friend void swap(Debouncer& lhs, Debouncer& rhs) noexcept {
            std::scoped_lock lk(lhs.m_mutex, rhs.m_mutex);

            using std::swap;
            swap(lhs.m_context, rhs.m_context);
            swap(lhs.m_func, rhs.m_func);
            swap(lhs.m_timer, rhs.m_timer);
            swap(lhs.m_connection, rhs.m_connection);
        }

        template <typename... Args>
        void operator()(Args&&... args) const {
            static_assert(std::is_invocable_v<std::decay_t<Func>&, Args...>,
                          "The debounced function cannot be called with the provided arguments.");
            std::lock_guard lk(m_mutex);

            if (!m_timer)
                return;

            if (*m_connection)
                QObject::disconnect(*m_connection);

            *m_connection = QObject::connect(
                m_timer,
                &QTimer::timeout,
                m_context,
                [=, packed_args=std::make_tuple(std::forward<Args>(args)...)]() {
                    std::apply(*m_func, std::move(packed_args));
                }
            );

            m_timer->start();
        }

        ~Debouncer() {
            std::lock_guard lk(m_mutex);
            if (*m_connection) {
                QObject::disconnect(*m_connection);
            }
        }

    private:
        QObject *m_context;
        std::unique_ptr<std::decay_t<Func>> m_func;
        QPointer<QTimer> m_timer;
        std::unique_ptr<QMetaObject::Connection> m_connection;
        mutable std::mutex m_mutex;
    };
}

/*!
 * \brief Creates a debounced version of a slot or callable.
 *
 * This function returns a new callable (a lambda) that, when invoked,
 * will delay the execution of the original function `func`. The execution is
 * delayed until the returned callable has not been invoked for `durationMs`
 * milliseconds.
 *
 * This is useful for signals that fire rapidly (e.g., `textChanged`, `mouseMove`)
 * to prevent the connected slot from running too frequently.
 *
 * \tparam Func The type of the callable (e.g., function pointer, lambda).
 * \param[in] func The function/slot to debounce. It must be a callable that can be
 * wrapped in `std::function`.
 * \param[in] context The `QObject` that will own the internal `QTimer`. This is crucial
 * for the timer's lifetime management.
 * \param[in] durationMs The debounce delay in milliseconds.
 * \return A new lambda function that you can connect to a signal.
 *
 * \note The returned debounced function is **movable but not copyable**.
 * This is because it uniquely owns the underlying timer and connection. You can
 * transfer ownership using `std::move`, but you cannot create a second,
 * independent copy.
 *
 * \note The lifetime of the internal `QTimer` is tied to the `context` object.
 * If the `context` object is destroyed, the debounced function will
 * cease to work.
 *
 * \note The arguments passed to the debounced function are copied and stored
 * internally. They are moved into the final function call when it executes.
 * This ensures that references to temporary objects remain valid.
 *
 * \code
 * // Example usage in a QWidget
 * QLineEdit *lineEdit = new QLineEdit(this);
 * QLabel *label = new QLabel(this);
 *
 * // Create a debounced function that updates a label
 * auto debouncedUpdate = debounce([label](const QString &text) {
 * label->setText("You typed: " + text);
 * }, this, 500); // Debounce for 500ms
 *
 * // Connect the textChanged signal to our debounced function
 * connect(lineEdit, &QLineEdit::textChanged, debouncedUpdate);
 *
 * // You can move it, for example, into a member variable
 * // m_debouncedUpdate = std::move(debouncedUpdate);
 * \endcode
 */
template <typename Func>
auto debounce(Func&& func, QObject* context, int durationMs = 300) {
    assert(context != nullptr && "Context object cannot be null.");
    assert(durationMs >= 0 && "Duration must be non-negative.");

    return [debouncer=detail::Debouncer(std::forward<Func>(func), context, durationMs)](auto&&... args) {
        debouncer(std::forward<decltype(args)>(args)...);
    };
}
#endif
