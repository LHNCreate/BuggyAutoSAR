//
// Created by leehaonan on 2024/9/8.
//

#ifndef BUGGYAUTOSAR_SAMPLEPTR_HPP
#define BUGGYAUTOSAR_SAMPLEPTR_HPP
#include <optional>

/**
 * @brief SamplePtr 大体上和std::unique_ptr类似
 * 但是由于其需要支持E2E的特性，因此需要单独实现
 *
 *
 */



template<typename T>
class SamplePtr {
public:
constexpr SamplePtr() noexcept;

constexpr SamplePtr(std::nullptr_t ) noexcept;

SamplePtr(const SamplePtr&) = delete;

SamplePtr(SamplePtr &&) noexcept;

~SamplePtr() noexcept;

SamplePtr& operator=(const SamplePtr&) = delete;

SamplePtr& operator=(SamplePtr&&) noexcept;

T& operator*() const noexcept;

T* operator->() const noexcept;

T* Get() const noexcept;

explicit operator bool() const noexcept;

void Swap(SamplePtr&) noexcept;

void Reset(std::nullptr_t );

//Todo)) E2E支持准备
//ara::com::e2e::ProfileCheckStatus GetProfileCheckStatus() const noexcept;


};














#endif   // BUGGYAUTOSAR_SAMPLEPTR_HPP
