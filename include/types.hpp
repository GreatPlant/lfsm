#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <string>

namespace {

///Пользовательский тип данных ternarMatrix для хранения тернарных матриц
using ternarMatrtix = std::vector<std::string>;

///Пользовательский тип данных ternarMatrix для хранения массива тернарных матриц
using ternarMatrixArray = std::vector<::ternarMatrtix>;

///Пользовательский тип данных ternarFunctions для хранения функций перехода
using ternarFunctions = std::pair<::ternarMatrixArray, ::ternarMatrixArray>;

}

#endif
