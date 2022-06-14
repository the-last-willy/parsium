#pragma once

#include "parsium/mckeeman.hpp"

parsium::mckeeman::GrammarBuilder json_format() {
	using namespace parsium::mckeeman;

	auto grammar =  parsium::mckeeman::GrammarBuilder();

	auto& json = grammar.add_rule("json");
	auto& value = grammar.add_rule("value");
	auto& object = grammar.add_rule("object");
	auto& members = grammar.add_rule("members");
	auto& member = grammar.add_rule("member");
	auto& array = grammar.add_rule("array");
	auto& elements = grammar.add_rule("elements");
	auto& element = grammar.add_rule("element");
	auto& string = grammar.add_rule("string");
	auto& characters = grammar.add_rule("characters");
	auto& character = grammar.add_rule("character");
	auto& escape = grammar.add_rule("escape");
	auto& hex = grammar.add_rule("hex");
	auto& number = grammar.add_rule("number");
	auto& integer = grammar.add_rule("integer");
	auto& digits = grammar.add_rule("digits");
	auto& digit = grammar.add_rule("digit");
	auto& onenine = grammar.add_rule("onenine");
	auto& fraction = grammar.add_rule("fraction");
	auto& exponent = grammar.add_rule("exponent");
	auto& sign = grammar.add_rule("sign");
	auto& ws = grammar.add_rule("ws");

	{
		auto& rule = json;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(element);
		}
	} {
		auto& rule = value;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(object);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(array);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(string);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(number);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item("true");
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item("false");
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item("null");
		}
	} {
		auto& rule = object;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('{');
			alternative.add_item(ws);
			alternative.add_item('}');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('{');
			alternative.add_item(members);
			alternative.add_item('}');
		}
	} {
		auto& rule = members;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(member);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(member);
			alternative.add_item(',');
			alternative.add_item(members);
		}
	} {
		auto& rule = member;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(ws);
			alternative.add_item(string);
			alternative.add_item(ws);
			alternative.add_item(':');
			alternative.add_item(element);
		}
	} {
		auto& rule = array;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('[');
			alternative.add_item(ws);
			alternative.add_item(']');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('[');
			alternative.add_item(elements);
			alternative.add_item(']');
		}
	} {
		auto& rule = elements;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(element);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(element);
			alternative.add_item(',');
			alternative.add_item(elements);
		}
	} {
		auto& rule = element;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(ws);
			alternative.add_item(value);
			alternative.add_item(ws);
		}
	} {
		auto& rule = string;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('"');
			alternative.add_item(characters);
			alternative.add_item('"');
		}
	} {
		auto& rule = characters;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(character);
			alternative.add_item(characters);
		}
	} {
		auto& rule = character;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(range(' ', 127) - exclude('"') - exclude('\\'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('\\');
			alternative.add_item(escape);
		}
	} {
		auto& rule = escape;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('"');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('\\');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('/');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('b');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('f');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('n');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('r');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('t');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('u');
			alternative.add_item(hex);
			alternative.add_item(hex);
			alternative.add_item(hex);
			alternative.add_item(hex);
		}
	} {
		auto& rule = hex;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(range('A', 'F'));
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(range('a', 'f'));
		}
	} {
		auto& rule = number;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(integer);
			alternative.add_item(fraction);
			alternative.add_item(exponent);
		}
	} {
		auto& rule = integer;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(onenine);
			alternative.add_item(digits);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('-');
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('-');
			alternative.add_item(onenine);
			alternative.add_item(digits);
		}
	} {
		auto& rule = digits;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(digit);
			alternative.add_item(digits);
		}
	} {
		auto& rule = digit;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('0');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(onenine);
		}
	} {
		auto& rule = onenine;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(range('1', '9'));
		}
	} {
		auto& rule = fraction;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('.');
			alternative.add_item(digits);
		}
	} {
		auto& rule = exponent;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('E');
			alternative.add_item(sign);
			alternative.add_item(digits);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('e');
			alternative.add_item(sign);
			alternative.add_item(digits);
		}
	} {
		auto& rule = sign;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item('+');
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item('-');
		}
	} {
		auto& rule = ws;
		rule.does_accept_nothing = true;
		{
			auto& alternative = rule.add_alternative();
			alternative.add_item(char(0x20));
			alternative.add_item(ws);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(char(0x0A));
			alternative.add_item(ws);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(char(0x0D));
			alternative.add_item(ws);
		} {
			auto& alternative = rule.add_alternative();
			alternative.add_item(char(0x09));
			alternative.add_item(ws);
		}
	}
	
	return grammar;
}
