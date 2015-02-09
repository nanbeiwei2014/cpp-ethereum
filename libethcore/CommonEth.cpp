/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file CommonEth.cpp
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#include "CommonEth.h"
#include <random>
#include <libdevcrypto/SHA3.h>
#include "Exceptions.h"
using namespace std;
using namespace dev;
using namespace dev::eth;

namespace dev
{
namespace eth
{

const unsigned c_protocolVersion = 53;
const unsigned c_databaseVersion = 5;

template <size_t n> constexpr u256 eth_unit() { return eth_unit<n-1>() * u256(1000); }
template <> constexpr u256 eth_unit<0>() { return u256(1); }

static const vector<pair<u256, string>> g_units =
{
	{eth_unit<18>(), "Uether"},
	{eth_unit<17>(), "Vether"},
	{eth_unit<16>(), "Dether"},
	{eth_unit<15>(), "Nether"},
	{eth_unit<14>(), "Yether"},
	{eth_unit<13>(), "Zether"},
	{eth_unit<12>(), "Eether"},
	{eth_unit<11>(), "Pether"},
	{eth_unit<10>(), "Tether"},
	{eth_unit<9>(), "Gether"},
	{eth_unit<8>(), "Mether"},
	{eth_unit<7>(), "grand"},
	{eth_unit<6>(), "ether"},
	{eth_unit<5>(), "finney"},
	{eth_unit<4>(), "szabo"},
	{eth_unit<3>(), "Gwei"},
	{eth_unit<2>(), "Mwei"},
	{eth_unit<1>(), "Kwei"},
	{eth_unit<0>(), "wei"}
};

vector<pair<u256, string>> const& units()
{
	return g_units;
}

std::string formatBalance(bigint const& _b)
{
	ostringstream ret;
	u256 b;
	if (_b < 0)
	{
		ret << "-";
		b = (u256)-_b;
	}
	else
		b = (u256)_b;

	if (b > g_units[0].first * 10000)
	{
		ret << (b / g_units[0].first) << " " << g_units[0].second;
		return ret.str();
	}
	ret << setprecision(5);
	for (auto const& i: g_units)
		if (i.first != 1 && b >= i.first * 100)
		{
			ret << (double(b / (i.first / 1000)) / 1000.0) << " " << i.second;
			return ret.str();
		}
	ret << b << " wei";
	return ret.str();
}

}}
