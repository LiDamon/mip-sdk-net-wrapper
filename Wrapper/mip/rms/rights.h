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
 * @brief Defines CommonRights, EditableDocumentRights, and EmailRights static helper classes
 * 
 * @file rights.h
 */

#ifndef API_MIP_RMS_RIGHTS_H_
#define API_MIP_RMS_RIGHTS_H_

#include <string>
#include <vector>

namespace mip {

/**
 * @brief Universally supported rights
 */
class CommonRights {
public:
  /**
   * @brief Gets string identifier for 'owner' right
   * 
   * @return String identifier for 'owner' right
   */
  static const std::string Owner() { return "OWNER"; }

  /**
   * @brief Gets string identifier for 'view' right
   * 
   * @return String identifier for 'view' right
   */
  static const std::string View() { return "VIEW"; }

  /**
   * @brief Gets string identifiers for 'view' and 'owner' rights
   * 
   * @return String identifiers for 'view' and 'owner' rights
   */
  static const std::vector<std::string> All() {
    return std::vector<std::string>{ CommonRights::View(), CommonRights::Owner() };
  }

  /**
   * @brief Gets string identifier for 'audited extract' right
   * 
   * @return String identifier for 'audited extract' right
   */
  static std::string AuditedExtract() { return "AUDITEDEXTRACT"; }

private:
  CommonRights() = delete;
};

/**
 * @brief Rights that apply to editable documents
 */
class EditableDocumentRights {
public:
  /**
   * @brief Gets string identifier for 'edit' right
   * 
   * @return String identifier for 'edit' right
   */
  static const std::string Edit() { return "EDIT"; }

  /**
   * @brief Gets string identifier for 'export' right
   * 
   * @return String identifier for 'export' right
   */
  static const std::string Export() { return "EXPORT"; }

  /**
   * @brief Gets string identifier for 'extract' right
   * 
   * @return String identifier for 'extract' right
   */
  static const std::string Extract() { return "EXTRACT"; }

  /**
   * @brief Gets string identifier for 'print' right
   * 
   * @return String identifier for 'print' right
   */
  static const std::string Print() { return "PRINT"; }

  /**
   * @brief Gets string identifier for 'comment' right
   * 
   * @return String identifier for 'comment' right
   */
  static const std::string Comment() { return "COMMENT"; }

  /**
   * @brief Gets string identifiers for 'view', 'owner', 'edit', 'extract', 'print', and 'comment' rights
   * 
   * @return String identifiers for 'view', 'owner', 'edit', 'extract', 'print', and 'comment' rights
   */
  static const std::vector<std::string> All() {
    return std::vector<std::string>{
        CommonRights::View(),
        EditableDocumentRights::Edit(),
        EditableDocumentRights::Extract(),
        EditableDocumentRights::Print(),
        EditableDocumentRights::Comment(),
        CommonRights::Owner()
    };
  }

private:
  EditableDocumentRights() = delete;
};

/**
 * @brief Rights that apply to email
 */
class EmailRights {
public:
  /**
   * @brief Gets string identifier for 'reply' right
   * 
   * @return String identifier for 'reply' right
   */
  static const std::string Reply() { return "REPLY"; }

  /**
   * @brief Gets string identifier for 'reply all' right
   * 
   * @return String identifier for 'reply all' right
   */
  static const std::string ReplyAll() { return "REPLYALL"; }

  /**
   * @brief Gets string identifier for 'forward' right
   * 
   * @return String identifier for 'forward' right
   */
  static const std::string Forward() { return "FORWARD"; }

  /**
   * @brief Gets string identifier for 'extract' right
   * 
   * @return String identifier for 'extract' right
   */
  static const std::string Extract() { return EditableDocumentRights::Extract(); }

  /**
   * @brief Gets string identifier for 'print' right
   * 
   * @return String identifier for 'print' right
   */
  static const std::string Print() { return EditableDocumentRights::Print(); }

  /**
   * @brief Gets string identifiers for 'view', 'owner', 'reply', 'reply all', 'forward', 'extract', and 'print' rights
   * 
   * @return String identifiers for 'view', 'owner', 'reply', 'reply all', 'forward', 'extract', and 'print' rights
   */
  static const std::vector<std::string> All() {
    return std::vector<std::string>{
        CommonRights::View(),
        EmailRights::Reply(),
        EmailRights::ReplyAll(),
        EmailRights::Forward(),
        EditableDocumentRights::Extract(),
        EditableDocumentRights::Print(),
        CommonRights::Owner()
    };
  }

private:
  EmailRights() = delete;
};

} // namespace mip

#endif // API_MIP_RMS_RIGHTS_H_
