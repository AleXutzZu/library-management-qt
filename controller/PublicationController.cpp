//
// Created by AleXutzZu on 21/05/2025.
//

#include "PublicationController.h"

PublicationController::PublicationController(std::unique_ptr<BasePublicationRepository> repository) : repository(
        std::move(repository)) {}
