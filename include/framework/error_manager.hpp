#ifndef ERROR_MANAGER_HPP
#define ERROR_MANAGER_HPP

#include <framework_build.hpp>
#include <generic/singleton.hpp>

#include <string>

namespace ai_framework::framework {
    enum ErrorType {
        NONE = -1,
        SUCCESS,
        INIT_FAILURE,
        RENDERER_FAILURE
    };

    /// <summary>
    /// Handles the storage of the last error occured globally.
    /// To Do: move this to an namespace; don't ever store this like an instance anymore
    /// </summary>
    struct AI_API ErrorManager : Singleton<ErrorManager> {
        ErrorManager() {
            clear_error();
        }

        std::string get_error_message() const {
            return message;
        }

        void print_error() {
            if (error != ErrorType::NONE && error != ErrorType::SUCCESS)
                printf("!!!!! Error %i: %s !!!!!\n", get_error_code(), message.c_str());
            else
                printf("Error %i: %s\n", get_error_code(), message.c_str());
        }

        int get_error_code() const {
            return error;
        }

        void clear_error() {
            set_error(ErrorType::NONE);
        }

        void set_error(ErrorType new_error, std::string_view new_message) {
            error = new_error;
            message = new_message;
        }

        void set_error(ErrorType error) {
            std::string message = "No description provided.";

            switch (error) {
            default: break;
            case ErrorType::SUCCESS:
                message = "The operation completed successfully!";
                break;
            case ErrorType::RENDERER_FAILURE:
                message = "A renderer error has occured.";
                break;
            }

            set_error(error, message);
        }

      private:
        std::string message;
        ErrorType error;
    };
} // namespace ai_framework

#endif