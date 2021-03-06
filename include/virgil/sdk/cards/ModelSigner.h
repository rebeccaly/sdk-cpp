/**
 * Copyright (C) 2015-2018 Virgil Security Inc.
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
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 */

#ifndef VIRGIL_SDK_MODELSIGNER_H
#define VIRGIL_SDK_MODELSIGNER_H

#include <memory>
#include <unordered_map>
#include <virgil/sdk/Common.h>
#include <virgil/sdk/crypto/Crypto.h>
#include <virgil/sdk/client/models/RawSignedModel.h>

namespace virgil {
    namespace sdk {
        namespace cards {
            /*!
             * @brief Class responsible for signing RawSignerModel
             */
            class ModelSigner {
            public:
                /*!
                 * @brief Constructor
                 * @param crypto std::shared_ptr to Crypto instance
                 */
                ModelSigner(std::shared_ptr<crypto::Crypto> crypto);

                /*!
                 * @brief signer identifier for self signatures
                 */
                static const std::string selfSignerIdentifier;

                /*!
                 * @brief Getter
                 * @return std::shared_ptr to Crypto instance
                 */
                const std::shared_ptr<crypto::Crypto>& crypto() const;

                /*!
                 * @brief Adds signature to given RawSignedModel with provided signer and PrivateKey
                 * @param model RawSignedModel to sign
                 * @param signer identifier of signer
                 * @param privateKey PrivateKey to sign with
                 */
                void sign(client::models::RawSignedModel &model,
                          const std::string &signer,
                          const crypto::keys::PrivateKey &privateKey) const;

                /*!
                 * @brief Adds signature to given RawSignedModel with provided signer, PrivateKey and additional data
                 * @param model RawSignedModel to sign
                 * @param signer identifier of signer
                 * @param privateKey PrivateKey to sign with
                 * @param additionalData additional data to sign with model
                 */
                void sign(client::models::RawSignedModel &model,
                          const std::string &signer,
                          const crypto::keys::PrivateKey &privateKey,
                          const VirgilByteArray &additionalData) const;

                /*!
                 * @brief Adds signature to given RawSignedModel with provided signer, PrivateKey and additional data
                 * @param model RawSignedModel to sign
                 * @param signer identifier of signer
                 * @param privateKey PrivateKey to sign with
                 * @param extraFields std::unordered_map with additional data to sign with model
                 */
                void sign(client::models::RawSignedModel &model,
                          const std::string &signer,
                          const crypto::keys::PrivateKey &privateKey,
                          const std::unordered_map<std::string, std::string> &extraFields) const;

                /*!
                 * @brief Adds owner's signature to given RawSignedModel using provided PrivateKey
                 * @param model RawSignedModel to sign
                 * @param privateKey PrivateKey to sign with
                 */
                void selfSign(client::models::RawSignedModel &model,
                              const crypto::keys::PrivateKey &privateKey) const;

                /*!
                 * @brief Adds owner's signature to given RawSignedModel using provided PrivateKey and additional data
                 * @param model RawSignedModel to sign
                 * @param privateKey PrivateKey to sign with
                 * @param additionalData additional data to sign with model
                 */
                void selfSign(client::models::RawSignedModel &model,
                              const crypto::keys::PrivateKey &privateKey,
                              const VirgilByteArray &additionalData) const;

                /*!
                 * @brief Adds owner's signature to given RawSignedModel using provided PrivateKey and additional data
                 * @param model RawSignedModel to sign
                 * @param privateKey PrivateKey to sign with
                 * @param extraFields std::unordered_map with additional data to sign with model
                 */
                void selfSign(client::models::RawSignedModel &model,
                              const crypto::keys::PrivateKey &privateKey,
                              const std::unordered_map<std::string, std::string> &extraFields) const;

            private:
                std::shared_ptr<crypto::Crypto> crypto_;
            };
        }
    }
}

#endif //VIRGIL_SDK_MODELSIGNER_H