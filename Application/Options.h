/* -*- C++ -*-
 *
 * FILE: Options.h
 *
 * URL: $HeadURL$
 *
 * @(#) $Id$
 *
 */
#ifndef Options_H
#define Options_H

#include <QString>
#include <QStringList>
#include <stdio.h>
#include <Basics/RandomSeed.h>

class QCoreApplication;

class Options {
public:
	Options(QCoreApplication&);

	enum Status { Ok = 0, CommandLine, Trouble };

	using Verbosity = unsigned int;
	Verbosity verbosity() const { return _verbosity; }

	/** Check the verbosity level.
	 *
	 * Usage:
	 * if (options.if_verbose(1))
	 *     std::cerr << "I'm doing something\n";
	 */
	bool verbose_if(Verbosity lvl) const {
		return verbosity() >= lvl;
	}

	/** Call a function, even a lambda function, if the verbosity is high
	 * enough.
	 *
	 * Usage:
	 * options.if_verbose(1, [](){ std::cerr << "I'm doing something\n"; } )
	 *
	 * Use [&](){...} if your output uses variables of the current scope.
	 */
	template<typename Lambda>
	void verbose_if(Verbosity lvl, Lambda&& lambda) const {
		if (verbose_if(lvl))
			std::forward<Lambda>(lambda)();
	}

	bool noOutput() const;
	bool useURI() const;
	QString getInputName() const;
	QString getOutputName() const;

	/* The seed is passed from the v1/LargeFile to the model - always. If
	 * neither -N nor -S is used, the context is not a Trace access and the
	 * values from the Settings are used. */
	enum SeedMode { Undefined, Seeded, NotSeeded };
	SeedMode getSeedMode() const { return _seedMode; }
	Basics::RandomSeed::ValueType getSeed() const { return _seed; }

private:
	static void showVersion();

	Verbosity _verbosity{1};
	bool _noOutput{false};
	bool _useURI{false};
	QString _inputName{"-"};
	QString _outputName{"-"};

	SeedMode _seedMode{Undefined};
	Basics::RandomSeed::ValueType _seed{1u};
};

#endif
