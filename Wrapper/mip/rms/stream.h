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
 * @brief Defines IStream interface
 * 
 * @file stream.h
 */

#ifndef API_MIP_RMS_STREAM_H_
#define API_MIP_RMS_STREAM_H_

#include <future>
#include <memory>
#include <string>
#include <vector>

#include "mip/mip_export.h"

namespace mip {

class IStream;

/**
 * @brief IStream shared pointer
 */
typedef std::shared_ptr<IStream> SharedStream;

/**
 * @brief Creates an IStream from a std::istream
 * 
 * @param stdIStream Backing std::istream
 * 
 * @return IStream wrapping a std::istream
 */
MIP_EXPORT mip::SharedStream CreateStreamFromStdStream(std::shared_ptr<std::istream> stdIStream);

/**
 * @brief Creates an IStream from a std::ostream
 * 
 * @param stdOStream Backing std::ostream
 * 
 * @return IStream wrapping a std::ostream
 */
MIP_EXPORT mip::SharedStream CreateStreamFromStdStream(std::shared_ptr<std::ostream> stdOStream);

/**
 * @brief Creates an IStream from a std::iostream
 * 
 * @param stdIOStream Backing std::iostream
 * 
 * @return IStream wrapping a std::iostream
 */
MIP_EXPORT mip::SharedStream CreateStreamFromStdStream(std::shared_ptr<std::iostream> stdIOStream);

/**
 * @brief Base interface for protected streams.
 * 
 * @note Ported from Windows::Storage::Streams::IRandomAccessStream::IRandomAccessStream and
 * Windows::Storage::Streams::FileRandomAccessStream::FileRandomAccessStream.
 * https://msdn.microsoft.com/en-us/library/windows/apps/windows.storage.streams.irandomaccessstream.aspx
 * https://msdn.microsoft.com/en-us/library/windows/apps/windows.storage.streams.filerandomaccessstream.aspx
 */
class IStream {
public:
  /**
   * @brief Reads a block of data from stream asynchronously
   * 
   * @param pbBuffer Buffer into which stream should be read
   * @param cbBuffer Size of buffer
   * @param cbOffset Offset from beginning of input stream where reading should begin 
   * @param launchType Async launch type
   * 
   * @return Async future containing actual number of bytes read
   * 
   * @note Ensure buffer exists until result is retreived from std::future
   */
  virtual std::shared_future<int64_t> ReadAsync(
      uint8_t* pbBuffer,
      int64_t cbBuffer,
      int64_t cbOffset,
      std::launch launchType) = 0;

  /**
   * @brief Writes a block of data into stream asynchronously
   * 
   * @param cpbBuffer Buffer of data to write
   * @param cbBuffer Size of buffer
   * @param cbOffset Offset from beginning of output stream to where writing should begin
   * @param launchType Async launch type
   * 
   * @return Async future containing actual number of bytes written
   * 
   * @note Ensure buffer exists until result is retreived from std::future
   */
  virtual std::shared_future<int64_t> WriteAsync(
      const uint8_t* cpbBuffer,
      int64_t cbBuffer,
      int64_t cbOffset,
      std::launch launchType) = 0;

  /**
   * @brief Flushes output stream buffer asynchronously
   * 
   * @param launchType Async launch type
   * 
   * @return Async future containing whether or not flush was successful
   */
  virtual std::future<bool> FlushAsync(std::launch launchType) = 0;

  /**
   * @brief Reads a block of data from stream synchronously
   * 
   * @param pbBuffer Buffer into which stream should be read
   * @param cbBuffer Size of buffer
   * 
   * @return Actual number of bytes read
   */
  virtual int64_t Read(uint8_t* pbBuffer, int64_t cbBuffer) = 0;

  /**
   * @brief Writes a block of data into stream synchronously
   * 
   * @param cpbBuffer Buffer of data to write
   * @param cbBuffer Size of buffer
   * 
   * @return Actual number of bytes written
   */
  virtual int64_t Write(const uint8_t* cpbBuffer, int64_t cbBuffer) = 0;

  /**
   * @brief Flushes output stream buffer synchronously
   * 
   * @return Whether or not flush was successful
   */
  virtual bool Flush() = 0;

  /**
   * @brief Clones stream
   * 
   * @return Cloned stream
   */
  virtual SharedStream Clone() = 0;

  /**
   * @brief Seeks to a position within the stream
   * 
   * @param u64Position Byte offset from beginning of stream
   */
  virtual void Seek(uint64_t u64Position) = 0;

  /**
   * @brief Gets whether or not stream can be read
   * 
   * @return Whether or not stream can be read
   */
  virtual bool CanRead() const = 0;

  /**
   * @brief Gets whether or not stream can be written
   * 
   * @return Whether or not stream can be written
   */
  virtual bool CanWrite() const = 0;

  /**
   * @brief Gets current position of stream from beginning (in bytes)
   * 
   * @return Current positition of stream from beginning (in bytes)
   */
  virtual uint64_t Position() = 0;

  /**
   * @brief Gets size of stream (in bytes)
   * 
   * @return Size of stream (in bytes)
   */
  virtual uint64_t Size() = 0;

  /**
   * @brief Sets size of stream (in bytes)
   * 
   * @param u64Value Size of stream (in bytes)
   */
  virtual void Size(uint64_t u64Value) = 0;

  /**
   * @brief Reads a block of data from stream synchronously
   * 
   * @param u64size Size of data to read (in bytes)
   * 
   * @return Vector of actual read data
   */
  virtual std::vector<uint8_t> Read(uint64_t u64size) {
    std::vector<uint8_t> plainText;

    if (u64size > 0) {
      plainText.resize(static_cast<size_t>(u64size));
      int actualSize = static_cast<int>(Read(&plainText[0], static_cast<int>(plainText.size())));
      plainText.resize(actualSize);
    }

    return plainText;
  }

  /** @cond DOXYGEN_HIDE */
protected:
  virtual ~IStream() {}
  /** @endcond */
}; // class IStream

} // namespace mip

#endif // API_MIP_RMS_STREAM_H_
