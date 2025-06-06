/* -*- C++ -*-
 *
 * Copyright (c) 2020-2024 INCHRON AG <info@inchron.com>
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
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
	Options( QCoreApplication& );

	enum Status { Ok = 0, CommandLine, Trouble };

	bool noOutput() const { return _noOutput; }
	bool withMemory() const { return _withMemory; }
	bool withDataFlowConnections() const { return _withDataFlowConnections; }
	QStringList getInputNames() const { return _inputNames; }
	QString getOutputName() const { return _outputName; }
	QString getMappingName() const { return _mappingName; }

	enum Mode { Pedantic, Relaxed };
	Mode getMode() const { return _mode; }

	bool isStableIntrinsicId() const { return _stable; }
	bool isStableIntrinsicIdFromHash() const { return _stableFromHash; }
	bool isStableIntrinsicIdFromValue() const { return _stableFromValue; }
	const QByteArray& getStableIntrinsicIdValue() { return _stableValue; }

	using Verbosity = unsigned int;
	Verbosity verbosity() const { return _verbosity; }

	/** Check the verbosity level.
	 *
	 * Usage:
	 * if (options.verbose_if(1))
	 *     std::cerr << "I'm doing something\n";
	 */
	bool verbose_if( Verbosity lvl ) const { return verbosity() >= lvl; }

	/** Call a function, even a lambda function, if the verbosity is high
	 * enough.
	 *
	 * Usage:
	 * options.if_verbose(1, [](){ std::cerr << "I'm doing something\n"; } )
	 *
	 * Use [&](){...} if your output uses variables of the current scope.
	 */
	template<typename Lambda>
	void verbose_if( Verbosity lvl, Lambda&& lambda ) const {
		if ( verbose_if( lvl ) )
			std::forward<Lambda>( lambda )();
	}

private:
	QCommandLineParser _parser;

	Q_NORETURN void showVersion();
	static QString getRootEcoreVersion();
	Q_NORETURN void showHelp( int exitCode );
	Q_NORETURN void installImporter();

	Verbosity _verbosity{ 1 };
	bool _noOutput{ false };
	QStringList _inputNames{ "-" };
	QString _outputName{ "-" };
	QString _mappingName{ "" };
	Mode _mode{ Relaxed };
	bool _stable{ true };
	bool _stableFromHash{ false };
	bool _stableFromValue{ false };
	QByteArray _stableValue{ "0" };
	bool _withMemory{ true };
	/* @todo [AM2INC-129] */
	bool _withDataFlowConnections{ false };
};

#endif
