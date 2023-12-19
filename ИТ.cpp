#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class User {
private:
    std::string username;
    std::string password;
    std::string name;

public:
    User(const std::string& username, const std::string& password, const std::string& name)
        : username(username), password(password), name(name) {}

    std::string getUsername() const {
        return username;
    }

    std::string getPassword() const {
        return password;
    }

    std::string getName() const {
        return name;
    }
};

class Chat {
private:
    std::vector<User> users;
    std::vector<std::string> messages;

public:
    void registerUser(const User& newUser) {
        for (const User& existingUser : users) {
            if (existingUser.getUsername() == newUser.getUsername()) {
                throw std::invalid_argument("Username уже используется. Пожалуйста, выберите другой.");
            }
        }
        users.push_back(newUser);
    }

    User loginUser(const std::string& username, const std::string& password) const {
        for (const User& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                return user;
            }
        }
        throw std::invalid_argument("Неправильное имя пользователя или пароль. Пожалуйста, попробуйте еще раз.");
    }

    void sendMessage(const User& sender, const std::string& message, const User* recipient = nullptr) {
        if (recipient) {
            messages.push_back(sender.getName() + " to " + recipient->getName() + ": " + message);
        }
        else {
            messages.push_back(sender.getName() + " to all: " + message);
        }
    }

    const std::vector<User>& getUsers() const {
        return users;
    }

    const std::vector<std::string>& getMessages() const {
        return messages;
    }
};

template <typename T>
T getUserInput(const std::string& prompt) {
    T input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

int main() {

    setlocale(LC_ALL, "Russian");

    Chat chat;

    while (true) {
        try {
            std::cout << "1. Register\n2. Login\n3. Отправить сообщение\n4. Вывести сообщения\n5. Exit\n";
            int choice = getUserInput<int>("Введите что вы хотите выбрать: ");

            switch (choice) {
            case 1: {
                std::string username = getUserInput<std::string>("Введите username: ");
                std::string password = getUserInput<std::string>("Введите password: ");
                std::string name = getUserInput<std::string>("Введите name: ");

                User newUser(username, password, name);
                chat.registerUser(newUser);
                std::cout << "Регистрация прошла успешно!\n";
                break;
            }

            case 2: {
                std::string username = getUserInput<std::string>("Введите username: ");
                std::string password = getUserInput<std::string>("Введите password: ");

                User loggedInUser = chat.loginUser(username, password);
                std::cout << "Авторизация успешна! Добро пожаловать " << loggedInUser.getName() << "!\n";
                break;
            }

            case 3: {
                if (chat.getUsers().empty()) {
                    std::cout << "В чате нет пользователей. Пожалуйста, сначала зарегистрируйтесь и войдите в систему.\n";
                    break;
                }

                std::string message = getUserInput<std::string>("Введите ваше сообщение: ");
                std::cout << "1. Отправить всем пользователям\n2. Отправить конкретному пользователю\n";
                int recipientChoice = getUserInput<int>("Введите что вы хотите выбрать: ");

                if (recipientChoice == 1) {
                    chat.sendMessage(chat.getUsers().front(), message);
                    std::cout << "Сообщение отправлено всем пользователям!\n";
                }
                else if (recipientChoice == 2) {
                    std::string recipientUsername = getUserInput<std::string>("Введите username получателя: ");
                    const User* recipient = nullptr;

                    for (const User& user : chat.getUsers()) {
                        if (user.getUsername() == recipientUsername) {
                            recipient = &user;
                            break;
                        }
                    }

                    if (recipient) {
                        chat.sendMessage(chat.getUsers().front(), message, recipient);
                        std::cout << "Сообщение отправлено на " << recipient->getName() << "!\n";
                    }
                    else {
                        std::cout << "Получатель не найден.\n";
                    }
                }
                else {
                    std::cout << "Неверный выбор. Пожалуйста, попробуйте еще раз.\n";
                }
                break;
            }

            case 4:
                for (const auto& message : chat.getMessages()) {
                    std::cout << message << std::endl;
                }
                break;

            case 5:
                std::cout << "Выход из чата. До свидания!\n";
                return 0;

            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте еще раз.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }

    return 0;
}
