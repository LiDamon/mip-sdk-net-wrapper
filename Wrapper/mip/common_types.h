/**
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief A file Containing the common types used by the upe, file and rms modules.
 * 
 * @file common_types.h
 */

#ifndef API_MIP_COMMON_TYPES_H_
#define API_MIP_COMMON_TYPES_H_

#include <exception>
#include <string>

/** @cond DOXYGEN_HIDE */
#define UNUSED(x) (void)x

#ifdef MSVC12
#define NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif
/** @encond */
namespace mip {
/**
 * @brief Layout for watermarks.
 */
enum class WatermarkLayout : unsigned int {
  HORIZONTAL, /**< Watermark layout is horizontal */
  DIAGONAL, /**< Watermark layout is diagonal */
};

/**
 * @brief Alignment for content marks (content header or content footer).
 */
enum class ContentMarkAlignment : unsigned int {
  LEFT, /**< Content marking is aligned to the left */
  RIGHT, /**< Content marking is aligned to the right */
  CENTER, /**< Content marking is aligned to the center */
};

/**
 * @brief The assignment method of the label on the document. Whether the Assignment of the label was done 
 * automatically, standard or as a privileded operation (The equivalent to an admistrator operation). 
 */
enum class AssignmentMethod : unsigned int {
  STANDARD, /**< Label assignment method is standard */
  PRIVILEGED,  /**< Label assignment method is privileged */
  AUTO,  /**< Label assignment method is automatic */
};

/**
 * @brief Content format.
 */
enum class ContentFormat : unsigned int {
  DEFAULT, /**< Content format is standard file format */
  EMAIL, /**< Content format is email format */
};

/**
 * @brief Get the Assignment Method Name.
 * 
 * @param metod The Assignment method.
 * @return a string representation of the assignment method.
 */
inline std::string GetAssignmentMethodName(AssignmentMethod method) {
  static std::string kMethodArray[] = { "Standard", "Privileged", "Auto" };
  return kMethodArray[static_cast<int>(method)];
}

/**
 * @brief Abstraction for identity.
 */
class Identity {
public:
  /**
   * @brief Creates a default instance. Use this when the email address of the user is not known.
   */
  Identity() { }
  /**
   * @brief Creates an instance with the given email address. Use this when the 
   * email address of the user is known.
   * 
   * @param email a string of the users email.
   */
  explicit Identity(const std::string& email) : mEmail(email) { }
  /**
   * @brief Get the email.
   * 
   * @return the email.
   */
  const std::string& GetEmail() const { return mEmail; }

private:
  std::string mEmail;
};

/**
 * @brief Delegate for auth related operations.
 */
class AuthDelegate {
public:
  /**
   * @brief a class that contains all the information required from the calling application in order to 
   * generate an oauth2 token.
   */
  class OAuth2Challenge {
  public:
    /**
     * @brief Construct a new OAuth2Challenge object
     * 
     * @param authority the authority the token needs to be generated against.
     * @param resource  the resource the token is set to.
     */
    OAuth2Challenge(const std::string& authority, const std::string& resource)
      : mAuthority(authority),
      mResource(resource) {
    }
    /**
     * @brief Get the authority string.
     * 
     * @return the authority string.
     */
    const std::string& GetAuthority() const { return mAuthority; }
    /**
     * @brief Get the resource string
     * 
     * @return the resource string.
     */
    const std::string& GetResource() const { return mResource; }
  private:
    std::string mAuthority;
    std::string mResource;
  };

  /**
   * @brief A class defining how the mip sdk expects the oauth2 token to be 
   * passed back into the sdk.
   */
  class OAuth2Token {
  public:
    /**
     * @brief Construct a new OAuth2Token object
     */
    OAuth2Token() {}
    /**
     * @brief Construct a new OAuth2Token object from an accessToken.
     * 
     * @param accessToken The actual access token passed into the sdk.
     */
    OAuth2Token(const std::string& accessToken)
      : mAccessToken(accessToken) {
    }
    /**
     * @brief Get the Access token string.
     * 
     * @return the access token string.
     */
    const std::string& GetAccessToken() const { return mAccessToken; }
    /**
     * @brief Set the Access Token string.
     * 
     * @param accessToken the access token string. 
     */
    void SetAccessToken(const std::string& accessToken)  { mAccessToken = accessToken; }
  private:
    std::string mAccessToken;
  };

  /**
   * @brief This method is called when an auth token is required for the policy engine with the given identity and the given challenge.
   * The client should return whether acquiring token was successful. If successful, it should initialize the given token object.
   *
   * @param identity
   * @param challenge
   * @param token
   */
  virtual bool AcquireOAuth2Token(
      const mip::Identity& identity,
      const OAuth2Challenge& challenge,
      OAuth2Token& token) = 0;
  /** @cond DOXYGEN_HIDE */
  virtual ~AuthDelegate() { }
protected:
  AuthDelegate() { }
  /** @endcond */
};

/**
 * @brief Application identifier as set in the aad portal.
 */
struct ApplicationInfo {
  std::string applicationId;
  std::string friendlyName;
};

/**
 * @brief Name of the setting to explicitly specify policy data.
 * 
 * @return the custom settings key.
 */
inline const std::string& GetCustomSettingPolicyDataName() {
  static const std::string kValue = "policy_data";
  return kValue;
}
/**
 * @brief Name of the setting to explicitly specify file path to export SCC policy data to.
 * 
 * @return the custom settings key.
 */
inline const std::string& GetCustomSettingExportPolicyFileName() {
  static const std::string kValue = "export_policy_file";
  return kValue;
}
/**
 * @brief Name of the setting to explicitly specify policy data file path.
 * 
 * @return the custom settings key.
 */
inline const std::string& GetCustomSettingPolicyDataFile() {
  static const std::string kValue = "policy_file";
  return kValue;
}

}  // namespace mip

#endif  // API_MIP_COMMON_TYPES_H_