// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * amalthea/model_forward.hpp
 * This file was created by EMF4CPP 2.0.0 and is copyrighted by the
 * respective user and/or provider of the processed ECORE model.
 *
 * EMF4CPP is free software. You can obtain it from
 * https://github.com/catedrasaes-umu/emf4cpp
 */

#ifndef _AMALTHEA_MODEL_FORWARD_HPP
#define _AMALTHEA_MODEL_FORWARD_HPP

#include <ecore_forward.hpp> // for EDataTypes

/*PROTECTED REGION ID(amalthea_model_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage

namespace amalthea
{
    namespace model
    {

// EDataType
        /*PROTECTED REGION ID(amalthea_model_Address) ENABLED START*/
        typedef long Address;
        /*PROTECTED REGION END*/
        /*PROTECTED REGION ID(amalthea_model_PositiveInt) ENABLED START*/
        typedef int PositiveInt;
        /*PROTECTED REGION END*/
        /*PROTECTED REGION ID(amalthea_model_PositiveLong) ENABLED START*/
        typedef long PositiveLong;
        /*PROTECTED REGION END*/
        /*PROTECTED REGION ID(amalthea_model_PositiveDouble) ENABLED START*/
        typedef double PositiveDouble;
        /*PROTECTED REGION END*/
        /*PROTECTED REGION ID(amalthea_model_NonNegativeInt) ENABLED START*/
        typedef int NonNegativeInt;
        /*PROTECTED REGION END*/
        /*PROTECTED REGION ID(amalthea_model_NonNegativeLong) ENABLED START*/
        typedef long NonNegativeLong;
        /*PROTECTED REGION END*/
        /*PROTECTED REGION ID(amalthea_model_NonNegativeDouble) ENABLED START*/
        typedef double NonNegativeDouble;
        /*PROTECTED REGION END*/

// EClass
// Amalthea
        class Amalthea;
        using Amalthea_ptr = ::ecore::Ptr<Amalthea>;

// CommonElements
        class CommonElements;
        using CommonElements_ptr = ::ecore::Ptr<CommonElements>;

// BaseObject
        class BaseObject;
        using BaseObject_ptr = ::ecore::Ptr<BaseObject>;

// ReferableObject
        class ReferableObject;
        using ReferableObject_ptr = ::ecore::Ptr<ReferableObject>;

// ReferableBaseObject
        class ReferableBaseObject;
        using ReferableBaseObject_ptr = ::ecore::Ptr<ReferableBaseObject>;

// IAnnotatable
        class IAnnotatable;
        using IAnnotatable_ptr = ::ecore::Ptr<IAnnotatable>;

// ITaggable
        class ITaggable;
        using ITaggable_ptr = ::ecore::Ptr<ITaggable>;

// INamed
        class INamed;
        using INamed_ptr = ::ecore::Ptr<INamed>;

// IReferable
        class IReferable;
        using IReferable_ptr = ::ecore::Ptr<IReferable>;

// IDisplayName
        class IDisplayName;
        using IDisplayName_ptr = ::ecore::Ptr<IDisplayName>;

// IDescription
        class IDescription;
        using IDescription_ptr = ::ecore::Ptr<IDescription>;

// INamespaceMember
        class INamespaceMember;
        using INamespaceMember_ptr = ::ecore::Ptr<INamespaceMember>;

// Tag
        class Tag;
        using Tag_ptr = ::ecore::Ptr<Tag>;

// Namespace
        class Namespace;
        using Namespace_ptr = ::ecore::Ptr<Namespace>;

// Classifier
        class Classifier;
        using Classifier_ptr = ::ecore::Ptr<Classifier>;

// CoreClassifier
        class CoreClassifier;
        using CoreClassifier_ptr = ::ecore::Ptr<CoreClassifier>;

// MemoryClassifier
        class MemoryClassifier;
        using MemoryClassifier_ptr = ::ecore::Ptr<MemoryClassifier>;

// TransmissionPolicy
        class TransmissionPolicy;
        using TransmissionPolicy_ptr = ::ecore::Ptr<TransmissionPolicy>;

// Quantity
        class Quantity;
        using Quantity_ptr = ::ecore::Ptr<Quantity>;

// TimeComparable
        class TimeComparable;
        using TimeComparable_ptr = ::ecore::Ptr<TimeComparable>;

// Time
        class Time;
        using Time_ptr = ::ecore::Ptr<Time>;

// Frequency
        class Frequency;
        using Frequency_ptr = ::ecore::Ptr<Frequency>;

// Voltage
        class Voltage;
        using Voltage_ptr = ::ecore::Ptr<Voltage>;

// DataSize
        class DataSize;
        using DataSize_ptr = ::ecore::Ptr<DataSize>;

// DataRateComparable
        class DataRateComparable;
        using DataRateComparable_ptr = ::ecore::Ptr<DataRateComparable>;

// DataRate
        class DataRate;
        using DataRate_ptr = ::ecore::Ptr<DataRate>;

// CustomProperty
        class CustomProperty;
        using CustomProperty_ptr = ::ecore::Ptr<CustomProperty>;

// Value
        class Value;
        using Value_ptr = ::ecore::Ptr<Value>;

// ListObject
        class ListObject;
        using ListObject_ptr = ::ecore::Ptr<ListObject>;

// StringObject
        class StringObject;
        using StringObject_ptr = ::ecore::Ptr<StringObject>;

// BigIntegerObject
        class BigIntegerObject;
        using BigIntegerObject_ptr = ::ecore::Ptr<BigIntegerObject>;

// ReferenceObject
        class ReferenceObject;
        using ReferenceObject_ptr = ::ecore::Ptr<ReferenceObject>;

// IntegerObject
        class IntegerObject;
        using IntegerObject_ptr = ::ecore::Ptr<IntegerObject>;

// LongObject
        class LongObject;
        using LongObject_ptr = ::ecore::Ptr<LongObject>;

// FloatObject
        class FloatObject;
        using FloatObject_ptr = ::ecore::Ptr<FloatObject>;

// DoubleObject
        class DoubleObject;
        using DoubleObject_ptr = ::ecore::Ptr<DoubleObject>;

// BooleanObject
        class BooleanObject;
        using BooleanObject_ptr = ::ecore::Ptr<BooleanObject>;

// NumericStatistic
        class NumericStatistic;
        using NumericStatistic_ptr = ::ecore::Ptr<NumericStatistic>;

// MinAvgMaxStatistic
        class MinAvgMaxStatistic;
        using MinAvgMaxStatistic_ptr = ::ecore::Ptr<MinAvgMaxStatistic>;

// SingleValueStatistic
        class SingleValueStatistic;
        using SingleValueStatistic_ptr = ::ecore::Ptr<SingleValueStatistic>;

// ITimeDeviation
        class ITimeDeviation;
        using ITimeDeviation_ptr = ::ecore::Ptr<ITimeDeviation>;

// TimeInterval
        class TimeInterval;
        using TimeInterval_ptr = ::ecore::Ptr<TimeInterval>;

// TimeConstant
        class TimeConstant;
        using TimeConstant_ptr = ::ecore::Ptr<TimeConstant>;

// TimeHistogram
        class TimeHistogram;
        using TimeHistogram_ptr = ::ecore::Ptr<TimeHistogram>;

// TimeHistogramEntry
        class TimeHistogramEntry;
        using TimeHistogramEntry_ptr = ::ecore::Ptr<TimeHistogramEntry>;

// BoundedTimeDistribution
        class BoundedTimeDistribution;
        using BoundedTimeDistribution_ptr = ::ecore::Ptr<BoundedTimeDistribution>;

// TruncatedTimeDistribution
        class TruncatedTimeDistribution;
        using TruncatedTimeDistribution_ptr = ::ecore::Ptr<TruncatedTimeDistribution>;

// TimeBoundaries
        class TimeBoundaries;
        using TimeBoundaries_ptr = ::ecore::Ptr<TimeBoundaries>;

// TimeStatistics
        class TimeStatistics;
        using TimeStatistics_ptr = ::ecore::Ptr<TimeStatistics>;

// TimeUniformDistribution
        class TimeUniformDistribution;
        using TimeUniformDistribution_ptr = ::ecore::Ptr<TimeUniformDistribution>;

// TimeGaussDistribution
        class TimeGaussDistribution;
        using TimeGaussDistribution_ptr = ::ecore::Ptr<TimeGaussDistribution>;

// TimeWeibullEstimatorsDistribution
        class TimeWeibullEstimatorsDistribution;
        using TimeWeibullEstimatorsDistribution_ptr = ::ecore::Ptr<TimeWeibullEstimatorsDistribution>;

// TimeBetaDistribution
        class TimeBetaDistribution;
        using TimeBetaDistribution_ptr = ::ecore::Ptr<TimeBetaDistribution>;

// IDiscreteValueDeviation
        class IDiscreteValueDeviation;
        using IDiscreteValueDeviation_ptr = ::ecore::Ptr<IDiscreteValueDeviation>;

// DiscreteValueInterval
        class DiscreteValueInterval;
        using DiscreteValueInterval_ptr = ::ecore::Ptr<DiscreteValueInterval>;

// DiscreteValueConstant
        class DiscreteValueConstant;
        using DiscreteValueConstant_ptr = ::ecore::Ptr<DiscreteValueConstant>;

// DiscreteValueHistogram
        class DiscreteValueHistogram;
        using DiscreteValueHistogram_ptr = ::ecore::Ptr<DiscreteValueHistogram>;

// DiscreteValueHistogramEntry
        class DiscreteValueHistogramEntry;
        using DiscreteValueHistogramEntry_ptr = ::ecore::Ptr<DiscreteValueHistogramEntry>;

// BoundedDiscreteValueDistribution
        class BoundedDiscreteValueDistribution;
        using BoundedDiscreteValueDistribution_ptr = ::ecore::Ptr<BoundedDiscreteValueDistribution>;

// TruncatedDiscreteValueDistribution
        class TruncatedDiscreteValueDistribution;
        using TruncatedDiscreteValueDistribution_ptr = ::ecore::Ptr<TruncatedDiscreteValueDistribution>;

// DiscreteValueBoundaries
        class DiscreteValueBoundaries;
        using DiscreteValueBoundaries_ptr = ::ecore::Ptr<DiscreteValueBoundaries>;

// DiscreteValueStatistics
        class DiscreteValueStatistics;
        using DiscreteValueStatistics_ptr = ::ecore::Ptr<DiscreteValueStatistics>;

// DiscreteValueUniformDistribution
        class DiscreteValueUniformDistribution;
        using DiscreteValueUniformDistribution_ptr = ::ecore::Ptr<DiscreteValueUniformDistribution>;

// DiscreteValueGaussDistribution
        class DiscreteValueGaussDistribution;
        using DiscreteValueGaussDistribution_ptr = ::ecore::Ptr<DiscreteValueGaussDistribution>;

// DiscreteValueWeibullEstimatorsDistribution
        class DiscreteValueWeibullEstimatorsDistribution;
        using DiscreteValueWeibullEstimatorsDistribution_ptr = ::ecore::Ptr<DiscreteValueWeibullEstimatorsDistribution>;

// DiscreteValueBetaDistribution
        class DiscreteValueBetaDistribution;
        using DiscreteValueBetaDistribution_ptr = ::ecore::Ptr<DiscreteValueBetaDistribution>;

// IContinuousValueDeviation
        class IContinuousValueDeviation;
        using IContinuousValueDeviation_ptr = ::ecore::Ptr<IContinuousValueDeviation>;

// ContinuousValueInterval
        class ContinuousValueInterval;
        using ContinuousValueInterval_ptr = ::ecore::Ptr<ContinuousValueInterval>;

// ContinuousValueConstant
        class ContinuousValueConstant;
        using ContinuousValueConstant_ptr = ::ecore::Ptr<ContinuousValueConstant>;

// ContinuousValueHistogram
        class ContinuousValueHistogram;
        using ContinuousValueHistogram_ptr = ::ecore::Ptr<ContinuousValueHistogram>;

// ContinuousValueHistogramEntry
        class ContinuousValueHistogramEntry;
        using ContinuousValueHistogramEntry_ptr = ::ecore::Ptr<ContinuousValueHistogramEntry>;

// BoundedContinuousValueDistribution
        class BoundedContinuousValueDistribution;
        using BoundedContinuousValueDistribution_ptr = ::ecore::Ptr<BoundedContinuousValueDistribution>;

// TruncatedContinuousValueDistribution
        class TruncatedContinuousValueDistribution;
        using TruncatedContinuousValueDistribution_ptr = ::ecore::Ptr<TruncatedContinuousValueDistribution>;

// ContinuousValueBoundaries
        class ContinuousValueBoundaries;
        using ContinuousValueBoundaries_ptr = ::ecore::Ptr<ContinuousValueBoundaries>;

// ContinuousValueStatistics
        class ContinuousValueStatistics;
        using ContinuousValueStatistics_ptr = ::ecore::Ptr<ContinuousValueStatistics>;

// ContinuousValueUniformDistribution
        class ContinuousValueUniformDistribution;
        using ContinuousValueUniformDistribution_ptr = ::ecore::Ptr<ContinuousValueUniformDistribution>;

// ContinuousValueGaussDistribution
        class ContinuousValueGaussDistribution;
        using ContinuousValueGaussDistribution_ptr = ::ecore::Ptr<ContinuousValueGaussDistribution>;

// ContinuousValueWeibullEstimatorsDistribution
        class ContinuousValueWeibullEstimatorsDistribution;
        using ContinuousValueWeibullEstimatorsDistribution_ptr = ::ecore::Ptr<ContinuousValueWeibullEstimatorsDistribution>;

// ContinuousValueBetaDistribution
        class ContinuousValueBetaDistribution;
        using ContinuousValueBetaDistribution_ptr = ::ecore::Ptr<ContinuousValueBetaDistribution>;

// Mode
        class Mode;
        using Mode_ptr = ::ecore::Ptr<Mode>;

// NumericMode
        class NumericMode;
        using NumericMode_ptr = ::ecore::Ptr<NumericMode>;

// EnumMode
        class EnumMode;
        using EnumMode_ptr = ::ecore::Ptr<EnumMode>;

// ModeLiteral
        class ModeLiteral;
        using ModeLiteral_ptr = ::ecore::Ptr<ModeLiteral>;

// ComponentsModel
        class ComponentsModel;
        using ComponentsModel_ptr = ::ecore::Ptr<ComponentsModel>;

// IComponentContainer
        class IComponentContainer;
        using IComponentContainer_ptr = ::ecore::Ptr<IComponentContainer>;

// IInterfaceContainer
        class IInterfaceContainer;
        using IInterfaceContainer_ptr = ::ecore::Ptr<IInterfaceContainer>;

// ISystem
        class ISystem;
        using ISystem_ptr = ::ecore::Ptr<ISystem>;

// ComponentInterface
        class ComponentInterface;
        using ComponentInterface_ptr = ::ecore::Ptr<ComponentInterface>;

// MainInterface
        class MainInterface;
        using MainInterface_ptr = ::ecore::Ptr<MainInterface>;

// SubInterface
        class SubInterface;
        using SubInterface_ptr = ::ecore::Ptr<SubInterface>;

// ComponentPort
        class ComponentPort;
        using ComponentPort_ptr = ::ecore::Ptr<ComponentPort>;

// ComponentStructure
        class ComponentStructure;
        using ComponentStructure_ptr = ::ecore::Ptr<ComponentStructure>;

// IComponentStructureMember
        class IComponentStructureMember;
        using IComponentStructureMember_ptr = ::ecore::Ptr<IComponentStructureMember>;

// Component
        class Component;
        using Component_ptr = ::ecore::Ptr<Component>;

// Composite
        class Composite;
        using Composite_ptr = ::ecore::Ptr<Composite>;

// System
        class System;
        using System_ptr = ::ecore::Ptr<System>;

// ComponentInstance
        class ComponentInstance;
        using ComponentInstance_ptr = ::ecore::Ptr<ComponentInstance>;

// Connector
        class Connector;
        using Connector_ptr = ::ecore::Ptr<Connector>;

// InterfaceChannel
        class InterfaceChannel;
        using InterfaceChannel_ptr = ::ecore::Ptr<InterfaceChannel>;

// QualifiedPort
        class QualifiedPort;
        using QualifiedPort_ptr = ::ecore::Ptr<QualifiedPort>;

// ConfigModel
        class ConfigModel;
        using ConfigModel_ptr = ::ecore::Ptr<ConfigModel>;

// EventConfig
        class EventConfig;
        using EventConfig_ptr = ::ecore::Ptr<EventConfig>;

// ConstraintsModel
        class ConstraintsModel;
        using ConstraintsModel_ptr = ::ecore::Ptr<ConstraintsModel>;

// RunnableSequencingConstraint
        class RunnableSequencingConstraint;
        using RunnableSequencingConstraint_ptr = ::ecore::Ptr<RunnableSequencingConstraint>;

// AffinityConstraint
        class AffinityConstraint;
        using AffinityConstraint_ptr = ::ecore::Ptr<AffinityConstraint>;

// SeparationConstraint
        class SeparationConstraint;
        using SeparationConstraint_ptr = ::ecore::Ptr<SeparationConstraint>;

// PairingConstraint
        class PairingConstraint;
        using PairingConstraint_ptr = ::ecore::Ptr<PairingConstraint>;

// ProcessConstraint
        class ProcessConstraint;
        using ProcessConstraint_ptr = ::ecore::Ptr<ProcessConstraint>;

// RunnableConstraint
        class RunnableConstraint;
        using RunnableConstraint_ptr = ::ecore::Ptr<RunnableConstraint>;

// DataConstraint
        class DataConstraint;
        using DataConstraint_ptr = ::ecore::Ptr<DataConstraint>;

// RunnableSeparationConstraint
        class RunnableSeparationConstraint;
        using RunnableSeparationConstraint_ptr = ::ecore::Ptr<RunnableSeparationConstraint>;

// ProcessSeparationConstraint
        class ProcessSeparationConstraint;
        using ProcessSeparationConstraint_ptr = ::ecore::Ptr<ProcessSeparationConstraint>;

// DataSeparationConstraint
        class DataSeparationConstraint;
        using DataSeparationConstraint_ptr = ::ecore::Ptr<DataSeparationConstraint>;

// RunnablePairingConstraint
        class RunnablePairingConstraint;
        using RunnablePairingConstraint_ptr = ::ecore::Ptr<RunnablePairingConstraint>;

// ProcessPairingConstraint
        class ProcessPairingConstraint;
        using ProcessPairingConstraint_ptr = ::ecore::Ptr<ProcessPairingConstraint>;

// DataPairingConstraint
        class DataPairingConstraint;
        using DataPairingConstraint_ptr = ::ecore::Ptr<DataPairingConstraint>;

// RunnableConstraintTarget
        class RunnableConstraintTarget;
        using RunnableConstraintTarget_ptr = ::ecore::Ptr<RunnableConstraintTarget>;

// ProcessConstraintTarget
        class ProcessConstraintTarget;
        using ProcessConstraintTarget_ptr = ::ecore::Ptr<ProcessConstraintTarget>;

// DataConstraintTarget
        class DataConstraintTarget;
        using DataConstraintTarget_ptr = ::ecore::Ptr<DataConstraintTarget>;

// TargetMemory
        class TargetMemory;
        using TargetMemory_ptr = ::ecore::Ptr<TargetMemory>;

// TargetCore
        class TargetCore;
        using TargetCore_ptr = ::ecore::Ptr<TargetCore>;

// TargetScheduler
        class TargetScheduler;
        using TargetScheduler_ptr = ::ecore::Ptr<TargetScheduler>;

// LabelGroup
        class LabelGroup;
        using LabelGroup_ptr = ::ecore::Ptr<LabelGroup>;

// RunnableGroup
        class RunnableGroup;
        using RunnableGroup_ptr = ::ecore::Ptr<RunnableGroup>;

// ProcessGroup
        class ProcessGroup;
        using ProcessGroup_ptr = ::ecore::Ptr<ProcessGroup>;

// LabelEntityGroup
        class LabelEntityGroup;
        using LabelEntityGroup_ptr = ::ecore::Ptr<LabelEntityGroup>;

// RunnableEntityGroup
        class RunnableEntityGroup;
        using RunnableEntityGroup_ptr = ::ecore::Ptr<RunnableEntityGroup>;

// ProcessEntityGroup
        class ProcessEntityGroup;
        using ProcessEntityGroup_ptr = ::ecore::Ptr<ProcessEntityGroup>;

// TagGroup
        class TagGroup;
        using TagGroup_ptr = ::ecore::Ptr<TagGroup>;

// AbstractEventChain
        class AbstractEventChain;
        using AbstractEventChain_ptr = ::ecore::Ptr<AbstractEventChain>;

// EventChain
        class EventChain;
        using EventChain_ptr = ::ecore::Ptr<EventChain>;

// SubEventChain
        class SubEventChain;
        using SubEventChain_ptr = ::ecore::Ptr<SubEventChain>;

// EventChainItem
        class EventChainItem;
        using EventChainItem_ptr = ::ecore::Ptr<EventChainItem>;

// EventChainReference
        class EventChainReference;
        using EventChainReference_ptr = ::ecore::Ptr<EventChainReference>;

// EventChainContainer
        class EventChainContainer;
        using EventChainContainer_ptr = ::ecore::Ptr<EventChainContainer>;

// TimingConstraint
        class TimingConstraint;
        using TimingConstraint_ptr = ::ecore::Ptr<TimingConstraint>;

// PhysicalSectionConstraint
        class PhysicalSectionConstraint;
        using PhysicalSectionConstraint_ptr = ::ecore::Ptr<PhysicalSectionConstraint>;

// SynchronizationConstraint
        class SynchronizationConstraint;
        using SynchronizationConstraint_ptr = ::ecore::Ptr<SynchronizationConstraint>;

// EventSynchronizationConstraint
        class EventSynchronizationConstraint;
        using EventSynchronizationConstraint_ptr = ::ecore::Ptr<EventSynchronizationConstraint>;

// EventChainSynchronizationConstraint
        class EventChainSynchronizationConstraint;
        using EventChainSynchronizationConstraint_ptr = ::ecore::Ptr<EventChainSynchronizationConstraint>;

// DelayConstraint
        class DelayConstraint;
        using DelayConstraint_ptr = ::ecore::Ptr<DelayConstraint>;

// EventChainLatencyConstraint
        class EventChainLatencyConstraint;
        using EventChainLatencyConstraint_ptr = ::ecore::Ptr<EventChainLatencyConstraint>;

// RepetitionConstraint
        class RepetitionConstraint;
        using RepetitionConstraint_ptr = ::ecore::Ptr<RepetitionConstraint>;

// DataAgeConstraint
        class DataAgeConstraint;
        using DataAgeConstraint_ptr = ::ecore::Ptr<DataAgeConstraint>;

// DataAge
        class DataAge;
        using DataAge_ptr = ::ecore::Ptr<DataAge>;

// DataAgeCycle
        class DataAgeCycle;
        using DataAgeCycle_ptr = ::ecore::Ptr<DataAgeCycle>;

// DataAgeTime
        class DataAgeTime;
        using DataAgeTime_ptr = ::ecore::Ptr<DataAgeTime>;

// Requirement
        class Requirement;
        using Requirement_ptr = ::ecore::Ptr<Requirement>;

// ProcessRequirement
        class ProcessRequirement;
        using ProcessRequirement_ptr = ::ecore::Ptr<ProcessRequirement>;

// RunnableRequirement
        class RunnableRequirement;
        using RunnableRequirement_ptr = ::ecore::Ptr<RunnableRequirement>;

// ArchitectureRequirement
        class ArchitectureRequirement;
        using ArchitectureRequirement_ptr = ::ecore::Ptr<ArchitectureRequirement>;

// ProcessChainRequirement
        class ProcessChainRequirement;
        using ProcessChainRequirement_ptr = ::ecore::Ptr<ProcessChainRequirement>;

// RequirementLimit
        class RequirementLimit;
        using RequirementLimit_ptr = ::ecore::Ptr<RequirementLimit>;

// CPUPercentageRequirementLimit
        class CPUPercentageRequirementLimit;
        using CPUPercentageRequirementLimit_ptr = ::ecore::Ptr<CPUPercentageRequirementLimit>;

// FrequencyRequirementLimit
        class FrequencyRequirementLimit;
        using FrequencyRequirementLimit_ptr = ::ecore::Ptr<FrequencyRequirementLimit>;

// PercentageRequirementLimit
        class PercentageRequirementLimit;
        using PercentageRequirementLimit_ptr = ::ecore::Ptr<PercentageRequirementLimit>;

// CountRequirementLimit
        class CountRequirementLimit;
        using CountRequirementLimit_ptr = ::ecore::Ptr<CountRequirementLimit>;

// TimeRequirementLimit
        class TimeRequirementLimit;
        using TimeRequirementLimit_ptr = ::ecore::Ptr<TimeRequirementLimit>;

// DataCoherencyGroup
        class DataCoherencyGroup;
        using DataCoherencyGroup_ptr = ::ecore::Ptr<DataCoherencyGroup>;

// DataStabilityGroup
        class DataStabilityGroup;
        using DataStabilityGroup_ptr = ::ecore::Ptr<DataStabilityGroup>;

// DataGroupScope
        class DataGroupScope;
        using DataGroupScope_ptr = ::ecore::Ptr<DataGroupScope>;

// ProcessScope
        class ProcessScope;
        using ProcessScope_ptr = ::ecore::Ptr<ProcessScope>;

// RunnableScope
        class RunnableScope;
        using RunnableScope_ptr = ::ecore::Ptr<RunnableScope>;

// ComponentScope
        class ComponentScope;
        using ComponentScope_ptr = ::ecore::Ptr<ComponentScope>;

// EventModel
        class EventModel;
        using EventModel_ptr = ::ecore::Ptr<EventModel>;

// Event
        class Event;
        using Event_ptr = ::ecore::Ptr<Event>;

// EventSet
        class EventSet;
        using EventSet_ptr = ::ecore::Ptr<EventSet>;

// EntityEvent
        class EntityEvent;
        using EntityEvent_ptr = ::ecore::Ptr<EntityEvent>;

// TriggerEvent
        class TriggerEvent;
        using TriggerEvent_ptr = ::ecore::Ptr<TriggerEvent>;

// CustomEvent
        class CustomEvent;
        using CustomEvent_ptr = ::ecore::Ptr<CustomEvent>;

// StimulusEvent
        class StimulusEvent;
        using StimulusEvent_ptr = ::ecore::Ptr<StimulusEvent>;

// ProcessEvent
        class ProcessEvent;
        using ProcessEvent_ptr = ::ecore::Ptr<ProcessEvent>;

// ProcessChainEvent
        class ProcessChainEvent;
        using ProcessChainEvent_ptr = ::ecore::Ptr<ProcessChainEvent>;

// RunnableEvent
        class RunnableEvent;
        using RunnableEvent_ptr = ::ecore::Ptr<RunnableEvent>;

// LabelEvent
        class LabelEvent;
        using LabelEvent_ptr = ::ecore::Ptr<LabelEvent>;

// ChannelEvent
        class ChannelEvent;
        using ChannelEvent_ptr = ::ecore::Ptr<ChannelEvent>;

// SemaphoreEvent
        class SemaphoreEvent;
        using SemaphoreEvent_ptr = ::ecore::Ptr<SemaphoreEvent>;

// ComponentEvent
        class ComponentEvent;
        using ComponentEvent_ptr = ::ecore::Ptr<ComponentEvent>;

// HWModel
        class HWModel;
        using HWModel_ptr = ::ecore::Ptr<HWModel>;

// HwStructure
        class HwStructure;
        using HwStructure_ptr = ::ecore::Ptr<HwStructure>;

// HwModule
        class HwModule;
        using HwModule_ptr = ::ecore::Ptr<HwModule>;

// HwDomain
        class HwDomain;
        using HwDomain_ptr = ::ecore::Ptr<HwDomain>;

// FrequencyDomain
        class FrequencyDomain;
        using FrequencyDomain_ptr = ::ecore::Ptr<FrequencyDomain>;

// PowerDomain
        class PowerDomain;
        using PowerDomain_ptr = ::ecore::Ptr<PowerDomain>;

// ProcessingUnit
        class ProcessingUnit;
        using ProcessingUnit_ptr = ::ecore::Ptr<ProcessingUnit>;

// Memory
        class Memory;
        using Memory_ptr = ::ecore::Ptr<Memory>;

// Cache
        class Cache;
        using Cache_ptr = ::ecore::Ptr<Cache>;

// HwFeatureCategory
        class HwFeatureCategory;
        using HwFeatureCategory_ptr = ::ecore::Ptr<HwFeatureCategory>;

// HwFeature
        class HwFeature;
        using HwFeature_ptr = ::ecore::Ptr<HwFeature>;

// HwPort
        class HwPort;
        using HwPort_ptr = ::ecore::Ptr<HwPort>;

// ConnectionHandler
        class ConnectionHandler;
        using ConnectionHandler_ptr = ::ecore::Ptr<ConnectionHandler>;

// HwConnection
        class HwConnection;
        using HwConnection_ptr = ::ecore::Ptr<HwConnection>;

// HwAccessElement
        class HwAccessElement;
        using HwAccessElement_ptr = ::ecore::Ptr<HwAccessElement>;

// HwDefinition
        class HwDefinition;
        using HwDefinition_ptr = ::ecore::Ptr<HwDefinition>;

// ProcessingUnitDefinition
        class ProcessingUnitDefinition;
        using ProcessingUnitDefinition_ptr = ::ecore::Ptr<ProcessingUnitDefinition>;

// ConnectionHandlerDefinition
        class ConnectionHandlerDefinition;
        using ConnectionHandlerDefinition_ptr = ::ecore::Ptr<ConnectionHandlerDefinition>;

// MemoryDefinition
        class MemoryDefinition;
        using MemoryDefinition_ptr = ::ecore::Ptr<MemoryDefinition>;

// CacheDefinition
        class CacheDefinition;
        using CacheDefinition_ptr = ::ecore::Ptr<CacheDefinition>;

// HwPath
        class HwPath;
        using HwPath_ptr = ::ecore::Ptr<HwPath>;

// HwAccessPath
        class HwAccessPath;
        using HwAccessPath_ptr = ::ecore::Ptr<HwAccessPath>;

// HwPathElement
        class HwPathElement;
        using HwPathElement_ptr = ::ecore::Ptr<HwPathElement>;

// HwDestination
        class HwDestination;
        using HwDestination_ptr = ::ecore::Ptr<HwDestination>;

// MappingModel
        class MappingModel;
        using MappingModel_ptr = ::ecore::Ptr<MappingModel>;

// SchedulerAllocation
        class SchedulerAllocation;
        using SchedulerAllocation_ptr = ::ecore::Ptr<SchedulerAllocation>;

// TaskAllocation
        class TaskAllocation;
        using TaskAllocation_ptr = ::ecore::Ptr<TaskAllocation>;

// ISRAllocation
        class ISRAllocation;
        using ISRAllocation_ptr = ::ecore::Ptr<ISRAllocation>;

// RunnableAllocation
        class RunnableAllocation;
        using RunnableAllocation_ptr = ::ecore::Ptr<RunnableAllocation>;

// MemoryMapping
        class MemoryMapping;
        using MemoryMapping_ptr = ::ecore::Ptr<MemoryMapping>;

// PhysicalSectionMapping
        class PhysicalSectionMapping;
        using PhysicalSectionMapping_ptr = ::ecore::Ptr<PhysicalSectionMapping>;

// OSModel
        class OSModel;
        using OSModel_ptr = ::ecore::Ptr<OSModel>;

// OsDataConsistency
        class OsDataConsistency;
        using OsDataConsistency_ptr = ::ecore::Ptr<OsDataConsistency>;

// DataStability
        class DataStability;
        using DataStability_ptr = ::ecore::Ptr<DataStability>;

// NonAtomicDataCoherency
        class NonAtomicDataCoherency;
        using NonAtomicDataCoherency_ptr = ::ecore::Ptr<NonAtomicDataCoherency>;

// Semaphore
        class Semaphore;
        using Semaphore_ptr = ::ecore::Ptr<Semaphore>;

// Scheduler
        class Scheduler;
        using Scheduler_ptr = ::ecore::Ptr<Scheduler>;

// TaskScheduler
        class TaskScheduler;
        using TaskScheduler_ptr = ::ecore::Ptr<TaskScheduler>;

// SchedulerAssociation
        class SchedulerAssociation;
        using SchedulerAssociation_ptr = ::ecore::Ptr<SchedulerAssociation>;

// InterruptController
        class InterruptController;
        using InterruptController_ptr = ::ecore::Ptr<InterruptController>;

// SchedulingParameters
        class SchedulingParameters;
        using SchedulingParameters_ptr = ::ecore::Ptr<SchedulingParameters>;

// ParameterExtension
        class ParameterExtension;
        using ParameterExtension_ptr = ::ecore::Ptr<ParameterExtension>;

// Algorithm
        class Algorithm;
        using Algorithm_ptr = ::ecore::Ptr<Algorithm>;

// InterruptSchedulingAlgorithm
        class InterruptSchedulingAlgorithm;
        using InterruptSchedulingAlgorithm_ptr = ::ecore::Ptr<InterruptSchedulingAlgorithm>;

// TaskSchedulingAlgorithm
        class TaskSchedulingAlgorithm;
        using TaskSchedulingAlgorithm_ptr = ::ecore::Ptr<TaskSchedulingAlgorithm>;

// FixedPriority
        class FixedPriority;
        using FixedPriority_ptr = ::ecore::Ptr<FixedPriority>;

// FixedPriorityPreemptive
        class FixedPriorityPreemptive;
        using FixedPriorityPreemptive_ptr = ::ecore::Ptr<FixedPriorityPreemptive>;

// FixedPriorityPreemptiveWithBudgetEnforcement
        class FixedPriorityPreemptiveWithBudgetEnforcement;
        using FixedPriorityPreemptiveWithBudgetEnforcement_ptr = ::ecore::Ptr<FixedPriorityPreemptiveWithBudgetEnforcement>;

// OSEK
        class OSEK;
        using OSEK_ptr = ::ecore::Ptr<OSEK>;

// DeadlineMonotonic
        class DeadlineMonotonic;
        using DeadlineMonotonic_ptr = ::ecore::Ptr<DeadlineMonotonic>;

// RateMonotonic
        class RateMonotonic;
        using RateMonotonic_ptr = ::ecore::Ptr<RateMonotonic>;

// Pfair
        class Pfair;
        using Pfair_ptr = ::ecore::Ptr<Pfair>;

// PfairPD2
        class PfairPD2;
        using PfairPD2_ptr = ::ecore::Ptr<PfairPD2>;

// PartlyPFairPD2
        class PartlyPFairPD2;
        using PartlyPFairPD2_ptr = ::ecore::Ptr<PartlyPFairPD2>;

// EarlyReleaseFairPD2
        class EarlyReleaseFairPD2;
        using EarlyReleaseFairPD2_ptr = ::ecore::Ptr<EarlyReleaseFairPD2>;

// PartlyEarlyReleaseFairPD2
        class PartlyEarlyReleaseFairPD2;
        using PartlyEarlyReleaseFairPD2_ptr = ::ecore::Ptr<PartlyEarlyReleaseFairPD2>;

// DynamicPriority
        class DynamicPriority;
        using DynamicPriority_ptr = ::ecore::Ptr<DynamicPriority>;

// LeastLocalRemainingExecutionTimeFirst
        class LeastLocalRemainingExecutionTimeFirst;
        using LeastLocalRemainingExecutionTimeFirst_ptr = ::ecore::Ptr<LeastLocalRemainingExecutionTimeFirst>;

// EarliestDeadlineFirst
        class EarliestDeadlineFirst;
        using EarliestDeadlineFirst_ptr = ::ecore::Ptr<EarliestDeadlineFirst>;

// PriorityBasedRoundRobin
        class PriorityBasedRoundRobin;
        using PriorityBasedRoundRobin_ptr = ::ecore::Ptr<PriorityBasedRoundRobin>;

// ReservationBasedServer
        class ReservationBasedServer;
        using ReservationBasedServer_ptr = ::ecore::Ptr<ReservationBasedServer>;

// DeferrableServer
        class DeferrableServer;
        using DeferrableServer_ptr = ::ecore::Ptr<DeferrableServer>;

// PollingPeriodicServer
        class PollingPeriodicServer;
        using PollingPeriodicServer_ptr = ::ecore::Ptr<PollingPeriodicServer>;

// SporadicServer
        class SporadicServer;
        using SporadicServer_ptr = ::ecore::Ptr<SporadicServer>;

// ConstantBandwidthServer
        class ConstantBandwidthServer;
        using ConstantBandwidthServer_ptr = ::ecore::Ptr<ConstantBandwidthServer>;

// ConstantBandwidthServerWithCASH
        class ConstantBandwidthServerWithCASH;
        using ConstantBandwidthServerWithCASH_ptr = ::ecore::Ptr<ConstantBandwidthServerWithCASH>;

// Grouping
        class Grouping;
        using Grouping_ptr = ::ecore::Ptr<Grouping>;

// UserSpecificSchedulingAlgorithm
        class UserSpecificSchedulingAlgorithm;
        using UserSpecificSchedulingAlgorithm_ptr = ::ecore::Ptr<UserSpecificSchedulingAlgorithm>;

// PriorityBased
        class PriorityBased;
        using PriorityBased_ptr = ::ecore::Ptr<PriorityBased>;

// OperatingSystem
        class OperatingSystem;
        using OperatingSystem_ptr = ::ecore::Ptr<OperatingSystem>;

// VendorOperatingSystem
        class VendorOperatingSystem;
        using VendorOperatingSystem_ptr = ::ecore::Ptr<VendorOperatingSystem>;

// OsOverhead
        class OsOverhead;
        using OsOverhead_ptr = ::ecore::Ptr<OsOverhead>;

// OsAPIOverhead
        class OsAPIOverhead;
        using OsAPIOverhead_ptr = ::ecore::Ptr<OsAPIOverhead>;

// OsISROverhead
        class OsISROverhead;
        using OsISROverhead_ptr = ::ecore::Ptr<OsISROverhead>;

// PropertyConstraintsModel
        class PropertyConstraintsModel;
        using PropertyConstraintsModel_ptr = ::ecore::Ptr<PropertyConstraintsModel>;

// CoreAllocationConstraint
        class CoreAllocationConstraint;
        using CoreAllocationConstraint_ptr = ::ecore::Ptr<CoreAllocationConstraint>;

// MemoryMappingConstraint
        class MemoryMappingConstraint;
        using MemoryMappingConstraint_ptr = ::ecore::Ptr<MemoryMappingConstraint>;

// ProcessAllocationConstraint
        class ProcessAllocationConstraint;
        using ProcessAllocationConstraint_ptr = ::ecore::Ptr<ProcessAllocationConstraint>;

// ProcessPrototypeAllocationConstraint
        class ProcessPrototypeAllocationConstraint;
        using ProcessPrototypeAllocationConstraint_ptr = ::ecore::Ptr<ProcessPrototypeAllocationConstraint>;

// RunnableAllocationConstraint
        class RunnableAllocationConstraint;
        using RunnableAllocationConstraint_ptr = ::ecore::Ptr<RunnableAllocationConstraint>;

// AbstractElementMappingConstraint
        class AbstractElementMappingConstraint;
        using AbstractElementMappingConstraint_ptr = ::ecore::Ptr<AbstractElementMappingConstraint>;

// Classification
        class Classification;
        using Classification_ptr = ::ecore::Ptr<Classification>;

// CoreClassification
        class CoreClassification;
        using CoreClassification_ptr = ::ecore::Ptr<CoreClassification>;

// MemoryClassification
        class MemoryClassification;
        using MemoryClassification_ptr = ::ecore::Ptr<MemoryClassification>;

// StimuliModel
        class StimuliModel;
        using StimuliModel_ptr = ::ecore::Ptr<StimuliModel>;

// Stimulus
        class Stimulus;
        using Stimulus_ptr = ::ecore::Ptr<Stimulus>;

// ModeValueList
        class ModeValueList;
        using ModeValueList_ptr = ::ecore::Ptr<ModeValueList>;

// ModeValueMapEntry
        class ModeValueMapEntry;
        using ModeValueMapEntry_ptr = ::ecore::Ptr<ModeValueMapEntry>;

// ModeValue
        class ModeValue;
        using ModeValue_ptr = ::ecore::Ptr<ModeValue>;

// ModeAssignment
        class ModeAssignment;
        using ModeAssignment_ptr = ::ecore::Ptr<ModeAssignment>;

// ModeConditionDisjunction
        class ModeConditionDisjunction;
        using ModeConditionDisjunction_ptr = ::ecore::Ptr<ModeConditionDisjunction>;

// ModeConditionDisjunctionEntry
        class ModeConditionDisjunctionEntry;
        using ModeConditionDisjunctionEntry_ptr = ::ecore::Ptr<ModeConditionDisjunctionEntry>;

// ModeCondition
        class ModeCondition;
        using ModeCondition_ptr = ::ecore::Ptr<ModeCondition>;

// ModeValueCondition
        class ModeValueCondition;
        using ModeValueCondition_ptr = ::ecore::Ptr<ModeValueCondition>;

// ModeLabelCondition
        class ModeLabelCondition;
        using ModeLabelCondition_ptr = ::ecore::Ptr<ModeLabelCondition>;

// ModeConditionConjunction
        class ModeConditionConjunction;
        using ModeConditionConjunction_ptr = ::ecore::Ptr<ModeConditionConjunction>;

// FixedPeriodic
        class FixedPeriodic;
        using FixedPeriodic_ptr = ::ecore::Ptr<FixedPeriodic>;

// PeriodicStimulus
        class PeriodicStimulus;
        using PeriodicStimulus_ptr = ::ecore::Ptr<PeriodicStimulus>;

// RelativePeriodicStimulus
        class RelativePeriodicStimulus;
        using RelativePeriodicStimulus_ptr = ::ecore::Ptr<RelativePeriodicStimulus>;

// VariableRateStimulus
        class VariableRateStimulus;
        using VariableRateStimulus_ptr = ::ecore::Ptr<VariableRateStimulus>;

// Scenario
        class Scenario;
        using Scenario_ptr = ::ecore::Ptr<Scenario>;

// PeriodicSyntheticStimulus
        class PeriodicSyntheticStimulus;
        using PeriodicSyntheticStimulus_ptr = ::ecore::Ptr<PeriodicSyntheticStimulus>;

// CustomStimulus
        class CustomStimulus;
        using CustomStimulus_ptr = ::ecore::Ptr<CustomStimulus>;

// SingleStimulus
        class SingleStimulus;
        using SingleStimulus_ptr = ::ecore::Ptr<SingleStimulus>;

// InterProcessStimulus
        class InterProcessStimulus;
        using InterProcessStimulus_ptr = ::ecore::Ptr<InterProcessStimulus>;

// PeriodicBurstStimulus
        class PeriodicBurstStimulus;
        using PeriodicBurstStimulus_ptr = ::ecore::Ptr<PeriodicBurstStimulus>;

// EventStimulus
        class EventStimulus;
        using EventStimulus_ptr = ::ecore::Ptr<EventStimulus>;

// ArrivalCurveStimulus
        class ArrivalCurveStimulus;
        using ArrivalCurveStimulus_ptr = ::ecore::Ptr<ArrivalCurveStimulus>;

// ArrivalCurveEntry
        class ArrivalCurveEntry;
        using ArrivalCurveEntry_ptr = ::ecore::Ptr<ArrivalCurveEntry>;

// Clock
        class Clock;
        using Clock_ptr = ::ecore::Ptr<Clock>;

// ClockFunction
        class ClockFunction;
        using ClockFunction_ptr = ::ecore::Ptr<ClockFunction>;

// ClockStepList
        class ClockStepList;
        using ClockStepList_ptr = ::ecore::Ptr<ClockStepList>;

// ClockStep
        class ClockStep;
        using ClockStep_ptr = ::ecore::Ptr<ClockStep>;

// SWModel
        class SWModel;
        using SWModel_ptr = ::ecore::Ptr<SWModel>;

// AbstractMemoryElement
        class AbstractMemoryElement;
        using AbstractMemoryElement_ptr = ::ecore::Ptr<AbstractMemoryElement>;

// AbstractProcess
        class AbstractProcess;
        using AbstractProcess_ptr = ::ecore::Ptr<AbstractProcess>;

// CustomEntity
        class CustomEntity;
        using CustomEntity_ptr = ::ecore::Ptr<CustomEntity>;

// ProcessChain
        class ProcessChain;
        using ProcessChain_ptr = ::ecore::Ptr<ProcessChain>;

// Process
        class Process;
        using Process_ptr = ::ecore::Ptr<Process>;

// IActivityGraphItemContainer
        class IActivityGraphItemContainer;
        using IActivityGraphItemContainer_ptr = ::ecore::Ptr<IActivityGraphItemContainer>;

// ActivityGraph
        class ActivityGraph;
        using ActivityGraph_ptr = ::ecore::Ptr<ActivityGraph>;

// ActivityGraphItem
        class ActivityGraphItem;
        using ActivityGraphItem_ptr = ::ecore::Ptr<ActivityGraphItem>;

// ModeSwitch
        class ModeSwitch;
        using ModeSwitch_ptr = ::ecore::Ptr<ModeSwitch>;

// ModeSwitchEntry
        class ModeSwitchEntry;
        using ModeSwitchEntry_ptr = ::ecore::Ptr<ModeSwitchEntry>;

// ModeSwitchDefault
        class ModeSwitchDefault;
        using ModeSwitchDefault_ptr = ::ecore::Ptr<ModeSwitchDefault>;

// ProbabilitySwitch
        class ProbabilitySwitch;
        using ProbabilitySwitch_ptr = ::ecore::Ptr<ProbabilitySwitch>;

// ProbabilitySwitchEntry
        class ProbabilitySwitchEntry;
        using ProbabilitySwitchEntry_ptr = ::ecore::Ptr<ProbabilitySwitchEntry>;

// Counter
        class Counter;
        using Counter_ptr = ::ecore::Ptr<Counter>;

// WaitEvent
        class WaitEvent;
        using WaitEvent_ptr = ::ecore::Ptr<WaitEvent>;

// SetEvent
        class SetEvent;
        using SetEvent_ptr = ::ecore::Ptr<SetEvent>;

// ClearEvent
        class ClearEvent;
        using ClearEvent_ptr = ::ecore::Ptr<ClearEvent>;

// EventMask
        class EventMask;
        using EventMask_ptr = ::ecore::Ptr<EventMask>;

// OsEvent
        class OsEvent;
        using OsEvent_ptr = ::ecore::Ptr<OsEvent>;

// InterProcessTrigger
        class InterProcessTrigger;
        using InterProcessTrigger_ptr = ::ecore::Ptr<InterProcessTrigger>;

// EnforcedMigration
        class EnforcedMigration;
        using EnforcedMigration_ptr = ::ecore::Ptr<EnforcedMigration>;

// SchedulePoint
        class SchedulePoint;
        using SchedulePoint_ptr = ::ecore::Ptr<SchedulePoint>;

// TerminateProcess
        class TerminateProcess;
        using TerminateProcess_ptr = ::ecore::Ptr<TerminateProcess>;

// Task
        class Task;
        using Task_ptr = ::ecore::Ptr<Task>;

// ISR
        class ISR;
        using ISR_ptr = ::ecore::Ptr<ISR>;

// ProcessPrototype
        class ProcessPrototype;
        using ProcessPrototype_ptr = ::ecore::Ptr<ProcessPrototype>;

// ChainedProcessPrototype
        class ChainedProcessPrototype;
        using ChainedProcessPrototype_ptr = ::ecore::Ptr<ChainedProcessPrototype>;

// GeneralPrecedence
        class GeneralPrecedence;
        using GeneralPrecedence_ptr = ::ecore::Ptr<GeneralPrecedence>;

// AccessPrecedenceSpec
        class AccessPrecedenceSpec;
        using AccessPrecedenceSpec_ptr = ::ecore::Ptr<AccessPrecedenceSpec>;

// OrderPrecedenceSpec
        class OrderPrecedenceSpec;
        using OrderPrecedenceSpec_ptr = ::ecore::Ptr<OrderPrecedenceSpec>;

// IDependsOn
        class IDependsOn;
        using IDependsOn_ptr = ::ecore::Ptr<IDependsOn>;

// DataDependency
        class DataDependency;
        using DataDependency_ptr = ::ecore::Ptr<DataDependency>;

// RunnableParameter
        class RunnableParameter;
        using RunnableParameter_ptr = ::ecore::Ptr<RunnableParameter>;

// Runnable
        class Runnable;
        using Runnable_ptr = ::ecore::Ptr<Runnable>;

// Label
        class Label;
        using Label_ptr = ::ecore::Ptr<Label>;

// Channel
        class Channel;
        using Channel_ptr = ::ecore::Ptr<Channel>;

// ModeLabel
        class ModeLabel;
        using ModeLabel_ptr = ::ecore::Ptr<ModeLabel>;

// Section
        class Section;
        using Section_ptr = ::ecore::Ptr<Section>;

// ComputationItem
        class ComputationItem;
        using ComputationItem_ptr = ::ecore::Ptr<ComputationItem>;

// ExecutionNeed
        class ExecutionNeed;
        using ExecutionNeed_ptr = ::ecore::Ptr<ExecutionNeed>;

// NeedEntry
        class NeedEntry;
        using NeedEntry_ptr = ::ecore::Ptr<NeedEntry>;

// Ticks
        class Ticks;
        using Ticks_ptr = ::ecore::Ptr<Ticks>;

// TicksEntry
        class TicksEntry;
        using TicksEntry_ptr = ::ecore::Ptr<TicksEntry>;

// ModeLabelAccess
        class ModeLabelAccess;
        using ModeLabelAccess_ptr = ::ecore::Ptr<ModeLabelAccess>;

// LabelAccess
        class LabelAccess;
        using LabelAccess_ptr = ::ecore::Ptr<LabelAccess>;

// ChannelAccess
        class ChannelAccess;
        using ChannelAccess_ptr = ::ecore::Ptr<ChannelAccess>;

// ChannelSend
        class ChannelSend;
        using ChannelSend_ptr = ::ecore::Ptr<ChannelSend>;

// ChannelReceive
        class ChannelReceive;
        using ChannelReceive_ptr = ::ecore::Ptr<ChannelReceive>;

// SemaphoreAccess
        class SemaphoreAccess;
        using SemaphoreAccess_ptr = ::ecore::Ptr<SemaphoreAccess>;

// SenderReceiverCommunication
        class SenderReceiverCommunication;
        using SenderReceiverCommunication_ptr = ::ecore::Ptr<SenderReceiverCommunication>;

// SenderReceiverRead
        class SenderReceiverRead;
        using SenderReceiverRead_ptr = ::ecore::Ptr<SenderReceiverRead>;

// SenderReceiverWrite
        class SenderReceiverWrite;
        using SenderReceiverWrite_ptr = ::ecore::Ptr<SenderReceiverWrite>;

// ServerCall
        class ServerCall;
        using ServerCall_ptr = ::ecore::Ptr<ServerCall>;

// SynchronousServerCall
        class SynchronousServerCall;
        using SynchronousServerCall_ptr = ::ecore::Ptr<SynchronousServerCall>;

// AsynchronousServerCall
        class AsynchronousServerCall;
        using AsynchronousServerCall_ptr = ::ecore::Ptr<AsynchronousServerCall>;

// GetResultServerCall
        class GetResultServerCall;
        using GetResultServerCall_ptr = ::ecore::Ptr<GetResultServerCall>;

// Group
        class Group;
        using Group_ptr = ::ecore::Ptr<Group>;

// CallArgument
        class CallArgument;
        using CallArgument_ptr = ::ecore::Ptr<CallArgument>;

// RunnableCall
        class RunnableCall;
        using RunnableCall_ptr = ::ecore::Ptr<RunnableCall>;

// CustomEventTrigger
        class CustomEventTrigger;
        using CustomEventTrigger_ptr = ::ecore::Ptr<CustomEventTrigger>;

// DataType
        class DataType;
        using DataType_ptr = ::ecore::Ptr<DataType>;

// CompoundType
        class CompoundType;
        using CompoundType_ptr = ::ecore::Ptr<CompoundType>;

// Struct
        class Struct;
        using Struct_ptr = ::ecore::Ptr<Struct>;

// StructEntry
        class StructEntry;
        using StructEntry_ptr = ::ecore::Ptr<StructEntry>;

// Array
        class Array;
        using Array_ptr = ::ecore::Ptr<Array>;

// Pointer
        class Pointer;
        using Pointer_ptr = ::ecore::Ptr<Pointer>;

// TypeRef
        class TypeRef;
        using TypeRef_ptr = ::ecore::Ptr<TypeRef>;

// Alias
        class Alias;
        using Alias_ptr = ::ecore::Ptr<Alias>;

// TypeDefinition
        class TypeDefinition;
        using TypeDefinition_ptr = ::ecore::Ptr<TypeDefinition>;

// DataTypeDefinition
        class DataTypeDefinition;
        using DataTypeDefinition_ptr = ::ecore::Ptr<DataTypeDefinition>;

// BaseTypeDefinition
        class BaseTypeDefinition;
        using BaseTypeDefinition_ptr = ::ecore::Ptr<BaseTypeDefinition>;

// Activation
        class Activation;
        using Activation_ptr = ::ecore::Ptr<Activation>;

// PeriodicActivation
        class PeriodicActivation;
        using PeriodicActivation_ptr = ::ecore::Ptr<PeriodicActivation>;

// VariableRateActivation
        class VariableRateActivation;
        using VariableRateActivation_ptr = ::ecore::Ptr<VariableRateActivation>;

// SporadicActivation
        class SporadicActivation;
        using SporadicActivation_ptr = ::ecore::Ptr<SporadicActivation>;

// SingleActivation
        class SingleActivation;
        using SingleActivation_ptr = ::ecore::Ptr<SingleActivation>;

// EventActivation
        class EventActivation;
        using EventActivation_ptr = ::ecore::Ptr<EventActivation>;

// CustomActivation
        class CustomActivation;
        using CustomActivation_ptr = ::ecore::Ptr<CustomActivation>;

// LabelAccessStatistic
        class LabelAccessStatistic;
        using LabelAccessStatistic_ptr = ::ecore::Ptr<LabelAccessStatistic>;

// RunEntityCallStatistic
        class RunEntityCallStatistic;
        using RunEntityCallStatistic_ptr = ::ecore::Ptr<RunEntityCallStatistic>;

// MeasurementModel
        class MeasurementModel;
        using MeasurementModel_ptr = ::ecore::Ptr<MeasurementModel>;

// Measurement
        class Measurement;
        using Measurement_ptr = ::ecore::Ptr<Measurement>;

// EventChainMeasurement
        class EventChainMeasurement;
        using EventChainMeasurement_ptr = ::ecore::Ptr<EventChainMeasurement>;

// TaskMeasurement
        class TaskMeasurement;
        using TaskMeasurement_ptr = ::ecore::Ptr<TaskMeasurement>;

// RunnableMeasurement
        class RunnableMeasurement;
        using RunnableMeasurement_ptr = ::ecore::Ptr<RunnableMeasurement>;

// EEnum

// RelationalOperator
        enum class RelationalOperator
        ;

// TimeUnit
        enum class TimeUnit
        ;

// FrequencyUnit
        enum class FrequencyUnit
        ;

// VoltageUnit
        enum class VoltageUnit
        ;

// DataSizeUnit
        enum class DataSizeUnit
        ;

// DataRateUnit
        enum class DataRateUnit
        ;

// SamplingType
        enum class SamplingType
        ;

// InterfaceKind
        enum class InterfaceKind
        ;

// RunnableOrderType
        enum class RunnableOrderType
        ;

// EventChainItemType
        enum class EventChainItemType
        ;

// SynchronizationType
        enum class SynchronizationType
        ;

// MappingType
        enum class MappingType
        ;

// LatencyType
        enum class LatencyType
        ;

// Severity
        enum class Severity
        ;

// LimitType
        enum class LimitType
        ;

// TimeMetric
        enum class TimeMetric
        ;

// CountMetric
        enum class CountMetric
        ;

// PercentageMetric
        enum class PercentageMetric
        ;

// CPUPercentageMetric
        enum class CPUPercentageMetric
        ;

// FrequencyMetric
        enum class FrequencyMetric
        ;

// CoherencyDirection
        enum class CoherencyDirection
        ;

// ProcessEventType
        enum class ProcessEventType
        ;

// RunnableEventType
        enum class RunnableEventType
        ;

// LabelEventType
        enum class LabelEventType
        ;

// ChannelEventType
        enum class ChannelEventType
        ;

// SemaphoreEventType
        enum class SemaphoreEventType
        ;

// ComponentEventType
        enum class ComponentEventType
        ;

// MemoryType
        enum class MemoryType
        ;

// StructureType
        enum class StructureType
        ;

// CacheType
        enum class CacheType
        ;

// PortType
        enum class PortType
        ;

// SchedPolicy
        enum class SchedPolicy
        ;

// WriteStrategy
        enum class WriteStrategy
        ;

// PuType
        enum class PuType
        ;

// PortInterface
        enum class PortInterface
        ;

// HwFeatureType
        enum class HwFeatureType
        ;

// MemoryAddressMappingType
        enum class MemoryAddressMappingType
        ;

// OsDataConsistencyMode
        enum class OsDataConsistencyMode
        ;

// AccessMultiplicity
        enum class AccessMultiplicity
        ;

// DataStabilityLevel
        enum class DataStabilityLevel
        ;

// SemaphoreType
        enum class SemaphoreType
        ;

// Condition
        enum class Condition
        ;

// GroupingType
        enum class GroupingType
        ;

// CurveType
        enum class CurveType
        ;

// WaitEventType
        enum class WaitEventType
        ;

// WaitingBehaviour
        enum class WaitingBehaviour
        ;

// ISRCategory
        enum class ISRCategory
        ;

// AccessPrecedenceType
        enum class AccessPrecedenceType
        ;

// OrderType
        enum class OrderType
        ;

// DirectionType
        enum class DirectionType
        ;

// LabelDataStability
        enum class LabelDataStability
        ;

// ModeLabelAccessEnum
        enum class ModeLabelAccessEnum
        ;

// ReceiveOperation
        enum class ReceiveOperation
        ;

// LabelAccessDataStability
        enum class LabelAccessDataStability
        ;

// LabelAccessEnum
        enum class LabelAccessEnum
        ;

// LabelAccessImplementation
        enum class LabelAccessImplementation
        ;

// SemaphoreAccessEnum
        enum class SemaphoreAccessEnum
        ;

// BlockingType
        enum class BlockingType
        ;

// Preemption
        enum class Preemption
        ;

// ConcurrencyType
        enum class ConcurrencyType
        ;

// ASILType
        enum class ASILType
        ;

// Package & Factory
        class ModelFactory;
        using ModelFactory_ptr = ::ecore::Ptr<ModelFactory>;
        class ModelPackage;
        using ModelPackage_ptr = ::ecore::Ptr<ModelPackage>;

    } // model
} // amalthea

#endif // _AMALTHEA_MODEL_FORWARD_HPP

