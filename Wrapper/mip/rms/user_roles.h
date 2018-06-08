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
 * @brief Defines UserRoles class
 * 
 * @file user_roles.h
 */

#ifndef API_MIP_RMS_USER_ROLES_H_
#define API_MIP_RMS_USER_ROLES_H_

#include <string>
#include <vector>

#include "mip/mip_export.h"

namespace mip {
/**
 * @brief Group of users
 */
typedef std::vector<std::string> UserList;

/**
 * @brief Set of roles
 */
typedef std::vector<std::string> RoleList;

/**
 * @brief Represents a group of users and the roles associated with them
 */
class UserRoles {
public:
  /**
   * @brief UserRoles constructor
   * 
   * @param users Group of users that share the same roles
   * @param roles Roles shared by group of users
   */
  MIP_EXPORT UserRoles(const UserList& users, const RoleList& roles);

  /**
   * @brief Gets users associated with a set of roles
   * 
   * @return Users associated with a set of roles
   */
  const UserList& Users() const { return mUsers; }

  /**
   * @brief Gets roles associated with a group of users
   * 
   * @return Roles associated with a group of users
   */
  const RoleList& Roles() const { return mRoles; }

private:
  void ValidateUsers(const UserList& users);
  void ValidateRoles(const RoleList& roles);

  UserList mUsers;
  RoleList mRoles;
};
} // namespace mip

#endif // API_MIP_RMS_USER_ROLES_H_
