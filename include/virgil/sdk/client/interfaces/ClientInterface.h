/**
 * Copyright (C) 2016 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VIRGIL_SDK_CLIENTINTERFACE_H
#define VIRGIL_SDK_CLIENTINTERFACE_H

#include <string>
#include <future>
#include <vector>

#include <virgil/sdk/client/models/Card.h>
#include <virgil/sdk/client/models/SearchCardsCriteria.h>
#include <virgil/sdk/client/models/requests/CreateCardRequest.h>
#include <virgil/sdk/client/models/requests/RevokeCardRequest.h>

namespace virgil {
namespace sdk {
namespace client {
    namespace interfaces {
        /*!
         * @brief This interface is designed for all interactions with the Virgil Service.
         */
        class ClientInterface {
        public:
            /*!
             * @brief Creates Virgil Card instance on the Virgil Cards Service.
             * Creates Virgil Card instance on the Virgil Cards Service and associates it with unique identifier.
             * Also makes the Card accessible for search/get/revoke queries from other users.
             * @note CreateCardRequest should be signed at least by Owner (Creator) and Application.
             *       Additional signatures may be applied if needed.
             * @see Card
             * @param request CreateCardRequest instance with Card data and signatures
             * @return std::future with Card
             */
            virtual std::future<models::Card> createCard(const models::requests::CreateCardRequest &request) const = 0;

            /*!
             * @brief Returns Virgil Card from the Virgil Cards Service with given ID, if exists.
             * @param cardId std::string with card ID
             * @return std::future with Card
             */
            virtual std::future<models::Card> getCard(const std::string &cardId) const = 0;

            /*!
             * @brief Performs search of Virgil Cards using search criteria on the Virgil Cards Service.
             * @param criteria SearchCardsCriteria instance with criteria for desired cards
             * @return std::future with std::vector which contains found cards
             */
            virtual std::future<std::vector<models::Card>> searchCards(
                    const models::SearchCardsCriteria &criteria) const = 0;

            /*!
             * @brief Revokes previously registered card.
             * @note RevokeCardRequest instance should be signed by Application.
             * @param request RevokeCardRequest with data for Card to be revoked
             * @return empty std::future
             */
            virtual std::future<void> revokeCard(const models::requests::RevokeCardRequest &request) const = 0;

            /*!
             * @brief Virtual destructor
             */
            virtual ~ClientInterface() = default;
        };
    }
}
}
}

#endif //VIRGIL_SDK_CLIENTINTERFACE_H