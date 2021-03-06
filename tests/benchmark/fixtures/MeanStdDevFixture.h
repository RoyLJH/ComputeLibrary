/*
 * Copyright (c) 2018 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef ARM_COMPUTE_TEST_MEAN_STD_DEV_FIXTURE
#define ARM_COMPUTE_TEST_MEAN_STD_DEV_FIXTURE

#include "arm_compute/core/TensorShape.h"
#include "arm_compute/core/Types.h"
#include "tests/Globals.h"
#include "tests/Utils.h"
#include "tests/framework/Fixture.h"

namespace arm_compute
{
namespace test
{
namespace benchmark
{
template <typename TensorType, typename Function, typename Accessor>
class MeanStdDevFixture : public framework::Fixture
{
public:
    template <typename...>
    void setup(const TensorShape &shape, Format format)
    {
        // Create tensors
        src = create_tensor<TensorType>(shape, format);

        // Create and configure function
        mean_std_dev_func.configure(&src, &mean, &std_dev);

        // Allocate tensors
        src.allocator()->allocate();
    }

    void run()
    {
        mean_std_dev_func.run();
    }

    void sync()
    {
        sync_if_necessary<TensorType>();
    }

    void teardown()
    {
        src.allocator()->free();
    }

private:
    TensorType src{};
    Function   mean_std_dev_func{};
    float      mean{ 0.0f };
    float      std_dev{ 0.0f };
};
} // namespace benchmark
} // namespace test
} // namespace arm_compute
#endif /* ARM_COMPUTE_TEST_MEAN_STD_DEV_FIXTURE */
