#pragma once

#include "parsium/mckeeman.hpp"

parsium::mckeeman::Grammar json_format() {
	using namespace parsium::mckeeman;
	
	auto grammar =  parsium::mckeeman::Grammar();
	
	auto& json = grammar.rules.emplace_back(rule("json"));
	auto& value = grammar.rules.emplace_back(rule("value"));
	auto& object = grammar.rules.emplace_back(rule("object"));
	auto& members = grammar.rules.emplace_back(rule("members"));
	auto& member = grammar.rules.emplace_back(rule("member"));
	auto& array = grammar.rules.emplace_back(rule("array"));
	auto& elements = grammar.rules.emplace_back(rule("elements"));
	auto& element = grammar.rules.emplace_back(rule("element"));
	auto& string = grammar.rules.emplace_back(rule("string"));
	auto& characters = grammar.rules.emplace_back(rule("characters"));
	auto& character = grammar.rules.emplace_back(rule("character"));
	auto& escape = grammar.rules.emplace_back(rule("escape"));
	auto& hex = grammar.rules.emplace_back(rule("hex"));
	auto& number = grammar.rules.emplace_back(rule("number"));
	auto& integer = grammar.rules.emplace_back(rule("integer"));
	auto& digits = grammar.rules.emplace_back(rule("digits"));
	auto& digit = grammar.rules.emplace_back(rule("digit"));
	auto& onenine = grammar.rules.emplace_back(rule("onenine"));
	auto& fraction = grammar.rules.emplace_back(rule("fraction"));
	auto& exponent = grammar.rules.emplace_back(rule("exponent"));
	auto& sign = grammar.rules.emplace_back(rule("sign"));
	auto& ws = grammar.rules.emplace_back(rule("ws"));

	{
		auto& rule = character;
	} {
		auto& rule = escape;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('"'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('\\'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('/'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('b'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('f'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('n'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('r'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('t'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('u'));
			alternative.items.emplace_back(hex);
			alternative.items.emplace_back(hex);
			alternative.items.emplace_back(hex);
			alternative.items.emplace_back(hex);
		}
	} {
		auto& rule = hex;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range('A', 'F'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range('a', 'f'));
		}
	} {
		auto& rule = number;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(integer);
			alternative.items.emplace_back(fraction);
			alternative.items.emplace_back(exponent);
		}
	} {
		auto& rule = integer;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(onenine);
			alternative.items.emplace_back(digits);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('-'));
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('-'));
			alternative.items.emplace_back(onenine);
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = digits;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(digit);
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = digit;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('0'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(onenine);
		}
	} {
		auto& rule = onenine;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(range('1', '9'));
		}
	} {
		auto& rule = fraction;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('.'));
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = exponent;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('E'));
			alternative.items.emplace_back(sign);
			alternative.items.emplace_back(digits);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('e'));
			alternative.items.emplace_back(sign);
			alternative.items.emplace_back(digits);
		}
	} {
		auto& rule = sign;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('+'));
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal('-'));
		}
	} {
		auto& rule = ws;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal(0x20));
			alternative.items.emplace_back(ws);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal(0x0A));
			alternative.items.emplace_back(ws);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal(0x0D));
			alternative.items.emplace_back(ws);
		} {
			auto& alternative = rule.alternatives.emplace_back();
			alternative.items.emplace_back(singleton_literal(0x09));
			alternative.items.emplace_back(ws);
		}
	}
	
	return grammar;
}