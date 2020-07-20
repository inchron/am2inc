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

#include <QCommandLineParser>
#include <QString>
#include <QStringList>

class QCoreApplication;

class Options {
public:
	/** The default constructor just initializes the QCommandLineParser. All
	 * other members are initialized by brace-or-equal initializers in the
	 * class declaration. */
	Options();

	/** Instantiating an Options object with a QCoreApplication will
	 * immediately process the command-line. */
	Options(QCoreApplication&);

	enum Status { Ok = 0, CommandLine, Trouble };

	bool noOutput() const { return _noOutput; }
	QStringList getInputNames() const { return _inputNames; }
	QString getOutputName() const { return _outputName; }
	QString getMappingName() const { return _mappingName; }

	enum Mode { Pedantic, Relaxed };
	Mode getMode() const { return _mode; }

	using Verbosity = unsigned int;
	Verbosity verbosity() const { return _verbosity; }

	/** Check the verbosity level.
	 *
	 * Usage:
	 * if (options.verbose_if(1))
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

private:
	QCommandLineParser _parser;

	Q_NORETURN void showVersion();
	Q_NORETURN void showHelp(int exitCode);

	Verbosity _verbosity{1};
	bool _noOutput{false};
	QStringList _inputNames{"-"};
	QString _outputName{"-"};
	QString _mappingName{""};
	Mode _mode{Relaxed};
};

#endif
