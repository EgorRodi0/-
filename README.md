Список участников команды:
Клепиков Егор
Родионов Егор 
Рыбинский Максим

Как были распределены задачи в команде:

Родионов + ChatGpt(в большей степени) писал код
Рыбинский + ChatGpt сделал архитектуру и схему 
Клепиков всё + ChatGpt оформил и написал этот документ


Описание выбранной идеи решения:

Проект представляет собой консольное приложение для обмена сообщениями между зарегистрированными пользователями. В приложении реализованы базовые функции, такие как регистрация новых пользователей, вход в систему, отправка сообщений всем пользователям или конкретному пользователю, а также отображение отправленных сообщений.

Схема архитектуры проекта:

+---------------------+      +-------------------------+
|       Main          |      |      InputHandler       |
|---------------------|      |-------------------------|
| - Основной цикл     |      | - getUserInput<T>()     |
| - Выбор действия    |      +-------------------------+
| - Вызов методов Chat|     
+---------------------+
           |
           v
+---------------------+
|        Chat         |
|---------------------|
| - users             |
| - messages          |
| + registerUser()    |
| + loginUser()       |
| + sendMessage()     |
| + getUsers()        |
| + getMessages()     |
+---------------------+
           |
           v
+---------------------+
|        User         |
|---------------------|
| - username          |
| - password          |
| - name              |
| + getUsername()     |
| + getPassword()     |
| + getName()         |
+---------------------+


Описание пользовательских типов и функций в проекте:

User
Свойства:
username - уникальное имя пользователя
password - пароль пользователя
name - имя пользователя
Методы:
Конструктор для создания пользователя
Геттеры для получения свойств пользователя
Chat
Свойства:
users (вектор пользователей) - хранение зарегистрированных пользователей
messages - (вектор строк) - хранение отправленных сообщений
Методы
registerUser - регистрация нового пользователя
loginUser - авторизация пользователя
sendMessage - отправка сообщения
Геттеры для получения списка пользователей и сообщений
InputHandler:
Методы:
template <typename> T> T getUserInput(const std::string& prompt) - обработка ввода пользователя
Main:
Основной цикл:
Отображение меню с выбором действий
Использование ‘InputHandler’ для получения ввода пользователя 
Обработка и выполнение выбранного действия с использованием методов ‘Chat’
