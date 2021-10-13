#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <QVector2D>
#include <QMutex>

class Controller
{
private:
    // [keys, action] key release event
    std::map<const std::vector<int>, std::function<void()>> m_key_bindings;

    // [keys, click, action] clicking event
    std::map<const std::pair<std::vector<int>, int>, std::function<void(QVector2D, QVector2D)>> m_click_bindings;
    
    // [keys, click, action] dragging events
    std::map<const std::pair<std::vector<int>, int>, std::function<void(QVector2D, QVector2D, QVector2D)>> m_drag_bindings;
    
    // [keys, action] moving events
    std::map<const std::vector<int>, std::function<void(QVector2D, QVector2D)>> m_move_bindings;
    
    // [keys, direction, action] mouse wheel events
    std::map<const std::pair<std::vector<int>, int>, std::function<void()>> m_wheel_bindings;

    std::map<const int, int> m_key_states;
    std::map<const int, int> m_last_key_states;
    
    std::map<const int, int> m_click_states;
    std::map<const int, int> m_last_click_states;
    
    int m_wheel_state;

    QVector2D m_mouse_pos;    
    QVector2D m_last_mouse_pos;
    QVector2D m_origin_mouse_pos;

    bool m_visible_cursor;
    bool m_capture_cursor;

    QMutex m_key_mutex;
    QMutex m_mouse_mutex;
    QMutex m_click_mutex;
    QMutex m_wheel_mutex;

public:
    Controller();
    virtual ~Controller();

    /*!
     * \brief Check all of the keys just released and execute the std::function associated 
     */
    void check();

    // ===== Key binding =====

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed
     * \param key the keycode to bind
     * \param action the function that should be executed
     */
    void bindKey(const int key, std::function<void()> action) {
        std::vector<int> temp = {key};
        m_key_bindings[temp] = action;
    };
    
    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed
     * \param keys keycode list to bind
     * \param action the function that should be executed
     */
    void bindKey(const std::vector<int> keys, std::function<void()> action) {
        m_key_bindings[keys] = action;
    };

    // ===== Click binding =====

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed 
     * \param click clickcode to bind
     * \param action the function that should be executed
     */
    void bindClick(const int click, std::function<void(QVector2D, QVector2D)> action) {
        std::vector<int> temp;
        m_click_bindings[std::pair<const std::vector<int>, int>(temp, click)] = action;
    };

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed 
     * \param key the keycode to bind
     * \param click clickcode to bind
     * \param action the function that should be executed
     */
    void bindClick(const int key, const int click, std::function<void(QVector2D, QVector2D)> action) {
        std::vector<int> temp = {key};
        m_click_bindings[std::pair<const std::vector<int>, int>(temp, click)] = action;
    };

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed 
     * \param keys the keycode list to bind
     * \param click clickcode to bind
     * \param action the function that should be executed
     */
    void bindClick(const std::vector<int> keys, const int click, std::function<void(QVector2D, QVector2D)> action) {
        m_click_bindings[std::pair<const std::vector<int>, int>(keys, click)] = action;
    };

    // ===== Drag binding =====

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed 
     * \param click clickcode to bind
     * \param action the function that should be executed
     */
    void bindDrag(const int click, std::function<void(QVector2D, QVector2D, QVector2D)> action) {
        std::vector<int> temp;
        m_drag_bindings[std::pair<const std::vector<int>, int>(temp, click)] = action;
    };

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed 
     * \param key the keycode to bind
     * \param click clickcode to bind
     * \param action the function that should be executed
     */
    void bindDrag(const int key, const int click, std::function<void(QVector2D, QVector2D, QVector2D)> action) {
        std::vector<int> temp = {key};
        m_drag_bindings[std::pair<const std::vector<int>, int>(temp, click)] = action;
    };

    /*!
     * \brief Bind a key to a std::function. Will be checked when key is pressed 
     * \param keys the keycode list to bind
     * \param click clickcode to bind
     * \param action the function that should be executed
     */
    void bindDrag(const std::vector<int> keys, const int click, std::function<void(QVector2D, QVector2D, QVector2D)> action) {
        m_drag_bindings[std::pair<const std::vector<int>, int>(keys, click)] = action;
    };

    // ===== Move binding =====

    /*!
     * \brief Bind simple move event to a std::function.
     * \param action the function that should be executed
     */
    void bindMove(std::function<void(QVector2D, QVector2D)> action) {
        std::vector<int> temp;
        m_move_bindings[temp] = action;
    };

    /*!
     * \brief Bind a key and a move to a std::function. Will be checked when key is pressed 
     * \param key the keycode to bind
     * \param action the function that should be executed
     */
    void bindMove(const int key, std::function<void(QVector2D, QVector2D)> action) {
        std::vector<int> temp = {key};
        m_move_bindings[temp] = action;
    };

    /*!
     * \brief Bind a key list to a std::function. Will be checked when all the keys are pressed together
     * \param keys the keycode list to bind
     * \param action the function that should be executed
     */
    void bindMove(const std::vector<int> keys, std::function<void(QVector2D, QVector2D)> action) {
        m_move_bindings[keys] = action;
    };

    // ===== Wheel binding =====

    /*!
     * \brief Bind simple wheel event to a std::function.
     * \param direction wheeling direction to bind
     * \param action the function that should be executed
     */
    void bindWheel(const int direction, std::function<void()> action) {
        std::vector<int> temp;
        m_wheel_bindings[std::pair<const std::vector<int>, int>(temp, direction)] = action;
    };

    /*!
     * \brief Bind a key and a direction to a std::function. Will be checked when key is pressed 
     * \param key the keycode to bind
     * \param direction wheeling direction to bind
     * \param action the function that should be executed
     */
    void bindWheel(const int key, const int direction, std::function<void()> action) {
        std::vector<int> temp = {key};
        m_wheel_bindings[std::pair<const std::vector<int>, int>(temp, direction)] = action;
    };

    /*!
     * \brief Bind a key list to a std::function. Will be checked when all the keys are pressed together
     * \param keys the keycode list to bind
     * \param direction wheeling direction to bind
     * \param action the function that should be executed
     */
    void bindWheel(const std::vector<int> keys, const int direction, std::function<void()> action) {
        m_wheel_bindings[std::pair<const std::vector<int>, int>(keys, direction)] = action;
    };

    // ==== Unbinding =====

    /*!
     * \brief Unbind a key, whatever press, pressing or released
     * \param key keycode to unbind
     */
    void unbind(const int key) {
        std::vector<int> temp = {key};
        m_key_bindings.erase(temp);
    };

    /*!
     * \brief Unbind every keys
     */
    void unbindKeys() {
        m_key_bindings.clear();
    };

    /*!
     * \brief Unbind every click
     */
    void unbindClicks() {
        m_click_bindings.clear();
    };

    /*!
     * \brief Unbind every drag
     */
    void unbindDrags() {
        m_drag_bindings.clear();
    };

    /*!
     * \brief Unbind every move
     */
    void unbindMoves() {
        m_move_bindings.clear();
    };

    // ===== Cursor behavior =====

    void toggleVisibleCursor() { 
        m_visible_cursor = !m_visible_cursor;
    };

    void toggleCaptureCursor() { 
        m_capture_cursor = !m_capture_cursor;
    };

    // ===== Event handling =====

    void keyEvent(const int key, const int state) {
        m_key_mutex.lock();
        m_last_key_states[key] = m_key_states[key];
        m_key_states[key] = state;
        m_key_mutex.unlock();
    };

    void clickEvent(const int key, const int state) {
        m_click_mutex.lock();
        m_last_click_states[key] = m_click_states[key];
        m_click_states[key] = state;
        if(state)
            m_origin_mouse_pos = m_mouse_pos;
        m_click_mutex.unlock();
    };

    void mouseEvent(int x, int y) {
        m_mouse_mutex.lock();
        m_last_mouse_pos = m_mouse_pos;
        m_mouse_pos.setX(x);
        m_mouse_pos.setY(y);
        m_mouse_mutex.unlock();
    };

    void wheelEvent(int d) {
        m_wheel_mutex.lock();
        m_wheel_state = d;
        m_wheel_mutex.unlock();
    };
};
