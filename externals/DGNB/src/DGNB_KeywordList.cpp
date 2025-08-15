/*	The NANDRAD data model library.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/

#include "DGNB_KeywordList.h"

#include <map>
#include <limits>
#include <iostream>

#include <IBK_FormatString.h>
#include <IBK_Exception.h>


namespace DGNB {
	/*! Holds the string to print as error when an invalid keyword is encountered. */
	const char * const INVALID_KEYWORD_INDEX_STRING = "KEYWORD_ERROR_STRING: Invalid type index";

	/*! Holds a list of all enum types/categories. */
	const char * const ENUM_TYPES[331] = {
		"Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages",
		"Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation",
		"Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination",
		"Eco1_1_2::para_t",
		"Eco1_1_2::EECBO_BuildingEnergyBill",
		"Eco1_1_2::EECBO_CircularEconomyBonusReuse",
		"Eco1_1_3::para_t",
		"Eco1_1_3::BRLCC_Calculation",
		"Eco2_4_1::ASBC_SiteAnalysis",
		"Eco2_4_1::ASBC_BuildingConceptAndSynergies",
		"Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies",
		"Eco2_4_2::ATPUS_ProofOfReusability",
		"Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors",
		"Eco2_4_3::para_t",
		"Eco2_4_3::DUTTC_DegreeOfUseOrTenancy",
		"Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants",
		"Eco2_4_4::para_t",
		"Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace",
		"Eco2_4_4::SE_MultipleUseOfSpace",
		"Eco2_4_4::SE_Agenda2030BonusSufficiency",
		"Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework",
		"Eco2_4_5::RA_BuildingConformToTaxonomy",
		"Eco2_4_6::A2030C_DigitalInfrastructure",
		"Eco2_4_7::A2030_Expandability",
		"Eco2_4_7::A2030_ImpulsAttractor",
		"Eco2_6_1::BCRMPV_PrePlanningphase4",
		"Eco2_6_1::BCRMPV_PostPlanningphase4",
		"Eco2_6_1::Agenda2030_CostBenefitAnalysis",
		"Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures",
		"Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures",
		"Eco2_6_2::ACC_GeneralResilienceToElementalDamages",
		"Eco2_6_2::ACC_Agenda2030HeadLoad",
		"Eco2_6_3::MAFERS_CompensationMeasuresAirQuality",
		"Eco2_6_3::MAFERS_CompensationMeasuresNoise",
		"Eco2_6_3::MAFERS_RadonRiskReduction",
		"Eco2_7_1::DCB_CurrentPlanningData",
		"Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation",
		"Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines",
		"Eco2_7_1::DCB_Agenda2030DigitalFootprint",
		"Eco2_7_2::ODBU_RevisionOperationMaintenancePlan",
		"Eco2_7_2::ODBU_OperatorFriendlyBuildingModel",
		"Eco2_7_3::PPBIM_Preparation",
		"Eco2_7_3::PPBIM_Creation",
		"Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM",
		"Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept",
		"Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck",
		"Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel",
		"Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions",
		"Eco2_7_5::DC_InformationOnBuildingRemovability",
		"Eco2_7_Alt::AC_CircularDigitalTwin",
		"Economy::para_weights",
		"Economy::para_goals",
		"Env1_1_1::CO2EarlyStage_OperatingEvaluation",
		"Env1_1_1::CO2EarlyStage_FurtherVariants",
		"Env1_1_1::CO2PlanningStage_OperatingEvaluation",
		"Env1_1_1::CO2PlanningStage_FurtherVariants",
		"Env1_1_1::CO2PlanningStage_EmissionOptimization",
		"Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding",
		"Env1_1_1::CO2Agenda2030MobilityOptimization",
		"Env1_1_2::para_t",
		"Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances",
		"Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue",
		"Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda",
		"Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency",
		"Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation",
		"Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase",
		"Env1_1_3::para_t",
		"Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance",
		"Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators",
		"Env1_2_1::para_t",
		"Env1_2_1::EFM_A",
		"Env1_2_1::EFM_BResidentialCommercial",
		"Env1_2_1::EFM_BShoppingCenter",
		"Env1_2_1::EFM_Agenda2030",
		"Env1_2_1::EFM_ExtraPointsForQS123",
		"Env1_3_1::RURPE_SupplyChainDiligence",
		"Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning",
		"Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation",
		"Env1_3_2::para_t",
		"Env1_3_2::RRM_CompanyResponsibilityForResourceManagement",
		"Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources",
		"Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry",
		"Env1_3_2::RRM_PRCEWMPS",
		"Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage",
		"Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept",
		"Env2_2_2::para_t",
		"Env2_2_2::DWDWWV_WaterUsageIndex",
		"Env2_2_3::DWDWWV_IrrigatioAndRetention",
		"Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure",
		"Env2_2_5::para_t",
		"Env2_2_5::DWDWWV_ContributionToSpongeCity",
		"Env2_2_5::DWDWWV_DrinkingWaterSanitation",
		"Env2_3_1::AD_DegreeOfConversion",
		"Env2_3_2::para_t",
		"Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures",
		"Env2_3_2::AD_CircularEconomyBonusUnsealing",
		"Env2_3_3::ADSQI_SoilRestoration",
		"Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection",
		"Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy",
		"Env2_4_2::para_t",
		"Env2_4_2::BDOS_BiotopeBiotopeSupportingArea",
		"Env2_4_2::BDOS_BiotopeGreenRoof",
		"Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding",
		"Env2_4_2::BDOS_DiversityOfStructures",
		"Env2_4_2::BDOS_Agenda2030BonusFertileSoil",
		"Env2_4_3::para_t",
		"Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies",
		"Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite",
		"Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue",
		"Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity",
		"Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept",
		"Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps",
		"Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan",
		"Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract",
		"Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl",
		"Env2_4_Alt::BDOS_AlternativeCertification",
		"Environment::para_weights",
		"Environment::para_goals",
		"KeywordList::MyParameters",
		"Pro1_1_1::RP_Basis",
		"Pro1_1_1::RP_RP",
		"Pro1_1_1::RP_Agenda2030FeasibilitySurvey",
		"Pro1_1_2::A2030_Participation",
		"Pro1_1_3::CS_SustainabilityRequirements",
		"Pro1_4_1::SATO_ExtentOfIntegration",
		"Pro1_4_1::SATO_CircularEconomyRecycledMaterials",
		"Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition",
		"Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod",
		"Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance",
		"Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod",
		"Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance",
		"Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign",
		"Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod",
		"Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod",
		"Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign",
		"Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam",
		"Pro1_6_2::R_RecommendationByIndependentDesignBoards",
		"Pro1_6_3::HAA_Recognition",
		"Pro2_1_1::NRCS_Concept",
		"Pro2_1_1::NRCS_InstructionOfOperators",
		"Pro2_1_1::NRCS_ExaminationOfImplementation",
		"Pro2_1_2::DRCS_Concept",
		"Pro2_1_2::DRCS_InstructionOfOperators",
		"Pro2_1_2::DRCS_ExaminationOfImplementation",
		"Pro2_1_3::SGPCS_Concept",
		"Pro2_1_3::SGPCS_InstructionOfOperators",
		"Pro2_1_3::SGPCS_ExaminationOfImplementation",
		"Pro2_1_4::WRCS_Concept",
		"Pro2_1_4::WRCS_InstructionOfOperators",
		"Pro2_1_4::WRCS_ExaminationOfImplementation",
		"Pro2_1_4::WRCS_CircularEconomyWastePrevention",
		"Pro2_1_5::C_ExternalSignageAndInformation",
		"Pro2_1_5::C_ExternalCommunicationWithResidents",
		"Pro2_1_5::C_InternalSharingOfInformation",
		"Pro2_1_6::RCWU_DataTransparency",
		"Pro2_1_6::RCWU_Concept",
		"Pro2_1_6::RCWU_InstructionOfOperators",
		"Pro2_1_6::RCWU_ExaminationOfImplementation",
		"Pro2_1_6::RCEU_DataTransparency",
		"Pro2_1_6::RCEU_Concept",
		"Pro2_1_6::RCEU_InstructionOfOperators",
		"Pro2_1_6::RCEU_ExaminationOfImplementation",
		"Pro2_1_7::M_Prevention",
		"Pro2_3_1::TM_PlanningPhase",
		"Pro2_3_2::TM_ConstructionPhase",
		"Pro2_3_3::TrialOperation",
		"Pro2_3_4::TM_FirstOperationPhase",
		"Pro2_3_5::TM_CompleteMonitoring",
		"Pro2_3_6::OperationStartUpManagement",
		"Pro2_3_7::BuildingPerformance",
		"Pro2_5_1::FM_Check",
		"Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions",
		"Pro2_5_3::FacilityManagerGuidebook",
		"Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation",
		"Pro2_5_5::SIS_Implementation",
		"Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation",
		"Pro2_5_6::OCP_Extended",
		"Process::para_weights",
		"Process::para_goals",
		"Site::para_weights",
		"Site::para_goals",
		"Site1_1_1::CR_ConductionOfAnalysis",
		"Site1_1_1::CR_Screening",
		"Site1_1_1::CR_SettingTheEvaluationPeriod",
		"Site1_1_1::CR_ActingOnTheEvaluation",
		"Site1_1_1::CR_Agenda2030ClimateProtectionGoal",
		"Site1_1_1::CR_DataBasis",
		"Site1_1_1::CR_ResultApplication",
		"Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange",
		"Site1_1_3::EEI_SurroundingNoise",
		"Site1_1_3::EEI_AirQuality",
		"Site1_1_3::EEI_Radon",
		"Site1_3_1::MIT_Surroundings",
		"Site1_3_1::MIT_RelationToBuilding",
		"Site1_3_2::PT_Stations",
		"Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures",
		"Site1_3_2::PT_Intervals",
		"Site1_3_2::PT_RelationToBuilding",
		"Site1_3_3::BT_CycleTrackWithin500Meters",
		"Site1_3_3::BT_Connection",
		"Site1_3_3::BT_RelationToBuilding",
		"Site1_3_4::FT_WalkwayNetworkWithin350Meters",
		"Site1_3_4::FT_CrossingOptionsWithin350Meters",
		"Site1_3_4::FT_SignageSystems",
		"Site1_3_5::AS_Within350Meters",
		"Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings",
		"Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure",
		"Site1_4_1::SI_WithinQuarterOrSurroundings",
		"Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces",
		"Site1_4_2::POE_InfrastructureInQuarterOrSurroundings",
		"Site1_4_3::BAIUD_InHouseDiversity",
		"Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange",
		"Soc1_1_1::para_t",
		"Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod",
		"Soc1_1_2::RH_RelativeHumidityHeatingPeriod",
		"Soc1_1_2::RH_RelativeHumidityCoolingPeriod",
		"Soc1_1_3::D_CoolingPeriod",
		"Soc1_1_4::RTAFT_CoolingPeriod",
		"Soc1_1_5::A2030CA_ResilientThermalComfort",
		"Soc1_1_6::UI_UserInfluence",
		"Soc1_1_Alt::AC_Innovation",
		"Soc1_2_1::para_t",
		"Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction",
		"Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore",
		"Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort",
		"Soc1_2_1::IHTVOC_WoodworkBonus",
		"Soc1_2_2::para_t",
		"Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare",
		"Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore",
		"Soc1_2_2::IH_AirChangeFrequencyResidential",
		"Soc1_2_2::IH_AirChangeLogisticsAndProduction",
		"Soc1_3_1::ORSR_HealthcareHotelAssembly",
		"Soc1_3_1::ORSR_Office",
		"Soc1_3_1::ORSR_Residential",
		"Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential",
		"Soc1_3_2::PAAC_RoomAcousticConcepts",
		"Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice",
		"Soc1_3_3::RA_Residential",
		"Soc1_4_1::para_t",
		"Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction",
		"Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding",
		"Soc1_4_2::para_t",
		"Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare",
		"Soc1_4_3::para_t",
		"Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter",
		"Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare",
		"Soc1_4_4::para_t",
		"Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare",
		"Soc1_4_4::DGS_ConvenienceStore",
		"Soc1_4_4::DGS_Logistics",
		"Soc1_4_4::DGS_Production",
		"Soc1_4_5::AL_LightingConcept",
		"Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements",
		"Soc1_4_6::SED_Residential",
		"Soc1_4_6::SED_HotelHealthcare",
		"Soc1_6_1::para_t",
		"Soc1_6_1::CSO_CommunicationZoneMainUsage",
		"Soc1_6_2::para_t",
		"Soc1_6_2::AOU_AdditionalOffersAndServices",
		"Soc1_6_2::AOU_OrientationInformation",
		"Soc1_6_3::para_t",
		"Soc1_6_3::FCEF_OnSiteOffers",
		"Soc1_6_4::para_t",
		"Soc1_6_4::QS_InnerAllotmentAreas",
		"Soc1_6_5::para_t",
		"Soc1_6_5::QS_DesignConceptForOutdoorAreas",
		"Soc1_6_5::QS_OutdoorCommonAreas",
		"Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse",
		"Soc1_6_5::QS_OutdoorCommonAreaComfort",
		"Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas",
		"Soc2_1_1::para_t",
		"Soc2_1_1::AQS_TotalQualityStage",
		"Socioculture::para_weights",
		"Socioculture::para_goals",
		"Tec1_3_1::PABE_PotentialOfFrontElements",
		"Tec1_3_2::TOES_EnvelopeParts",
		"Tec1_3_2::TOES_ThermalBridgeSurcharge",
		"Tec1_3_3::para_t",
		"Tec1_3_3::ABE_Measuring",
		"Tec1_3_4::para_t",
		"Tec1_3_4::HIS_VerificationAndVariations",
		"Tec1_3_5::QA_MeasuringQualityControl",
		"Tec1_4_1::PS_Planning",
		"Tec1_4_1::PS_Implementation",
		"Tec1_4_2::AAOTIRE_Warmth",
		"Tec1_4_2::AAOTIRE_Cooling",
		"Tec1_4_3::ABS_SystemsEngineeringAndCreation",
		"Tec1_4_3::ABS_DuctsTracesAllocation",
		"Tec1_4_4::IS_StateAndUpgradability",
		"Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems",
		"Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings",
		"Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings",
		"Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution",
		"Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem",
		"Tec1_4_5::URE_EnergySources",
		"Tec1_4_5::URE_Production",
		"Tec1_6_1::CC_ProjectIncludesDemolition",
		"Tec1_6_1::SSAPPD_Analysis",
		"Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse",
		"Tec1_6_1::SSAPPD_DemolitionJustification",
		"Tec1_6_1::SSAPPD_DemolitionExecution",
		"Tec1_6_1::SSAPPD_DemolitionAlternativeCertification",
		"Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite",
		"Tec1_6_2::CC_ProjectIncludesDemolition",
		"Tec1_6_2::CCCP_GoalAndFocusDefinition",
		"Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase",
		"Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase",
		"Tec1_6_3::para_t",
		"Tec1_6_3::CC_ProjectIncludesDemolition",
		"Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass",
		"Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel",
		"Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel",
		"Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations",
		"Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions",
		"Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation",
		"Tec3_1_1::MI_MobilityConcept",
		"Tec3_1_2::I_PedestrianInfrastructure",
		"Tec3_1_2::I_BicycleInfrastructure",
		"Tec3_1_2::I_MotorisedIndividualTransport",
		"Tec3_1_2::I_Agenda2030MobilityManagementConcept",
		"Tec3_1_3::para_t",
		"Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles",
		"Tec3_1_3::IAFS_MotorisedIndividualTransport",
		"Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations",
		"Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals",
		"Tec3_1_4::para_t",
		"Tec3_1_4::RS_MobilitySharing",
		"Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants",
		"Technology::para_weights",
		"Technology::para_goals",
		"Utilities::UsageType"
	};

	/*! Converts a category string to respective enumeration value. */
	int enum2index(const std::string & enumtype) {
		for (int i=0; i<331; ++i) {
			if (enumtype == ENUM_TYPES[i]) return i;
		}
		//std::cerr << "Unknown enumeration type '" << enumtype<< "'." << std::endl;
		return -1;
	}
	

	/*! Returns a keyword string for a given category (typenum) and type number t. */
	const char * theKeyword(int typenum, int t) {
		switch (typenum) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 :
			switch (t) {
				case 0 : return "LCCCPIES_Var1SubmissionOfCO2OrClimateCosts";
				case 1 : return "LCCCPIES_Var2SubmissionOfEcologicalSuggestions";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 :
			switch (t) {
				case 0 : return "LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 :
			switch (t) {
				case 0 : return "LCCCPIPE_PartialExaminationsDuringLP2";
				case 1 : return "LCCCPIPE_PartialExaminationsDuringLP3";
				case 2 : return "LCCCPIPE_PartialExaminationsDuringLP4";
				case 3 : return "LCCCPIPE_FundingAdviceSessionByEndOfLP4";
				case 4 : return "LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner";
			} break;
			// Eco1_1_2::para_t
			case 3 :
			switch (t) {
				case 0 : return "CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse";
			} break;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 :
			switch (t) {
				case 0 : return "EECBOBEB_BuildingUpToInnovationClauseStandards";
				case 1 : return "EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter";
			} break;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 :
			switch (t) {
				case 0 : return "EECBOCEBR_CircularEconomySolutionsForReuseSubmitted";
				case 1 : return "EECBOCEBR_LCCModelIncludesEndOfLifeCosts";
				case 2 : return "EECBOCEBR_DocumentationOfRawMaterialValue";
				case 3 : return "currentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse";
			} break;
			// Eco1_1_3::para_t
			case 6 :
			switch (t) {
				case 0 : return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue";
				case 1 : return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue";
				case 2 : return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue";
				case 3 : return "CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts";
				case 4 : return "CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC";
				case 5 : return "ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII";
			} break;
			// Eco1_1_3::BRLCC_Calculation
			case 7 :
			switch (t) {
				case 0 : return "BRLCCC_NetLifeCycleCostsResultsSubmitted";
				case 1 : return "BRLCCC_DisplayCaseFlag";
				case 2 : return "BRLCCC_HealthCareTypeIIFlag";
			} break;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 :
			switch (t) {
				case 0 : return "ASBCSA_GeneralPerceptionOfSite";
				case 1 : return "ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite";
				case 2 : return "ASBCSA_ImmediateNeighbourhood";
			} break;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 :
			switch (t) {
				case 0 : return "ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis";
				case 1 : return "ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects";
			} break;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 :
			switch (t) {
				case 0 : return "ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam";
				case 1 : return "ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes";
				case 2 : return "ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces";
				case 3 : return "ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements";
				case 4 : return "ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding";
				case 5 : return "ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios";
				case 6 : return "ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation";
			} break;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 :
			switch (t) {
				case 0 : return "ATPUSPR_SameUsageType";
				case 1 : return "ATPUSPR_DifferentUsageType";
			} break;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 :
			switch (t) {
				case 0 : return "ATPUSPAIF_CeilingHeight";
				case 1 : return "ATPUSPAIF_BuildingDepth";
				case 2 : return "ATPUSPAIF_FloorAllotment";
				case 3 : return "ATPUSPAIF_GroundPlanFlexibility";
				case 4 : return "ATPUSPAIF_Construction";
				case 5 : return "ATPUSPAIF_BuildingServices";
			} break;
			// Eco2_4_3::para_t
			case 13 :
			switch (t) {
				case 0 : return "CurrentValue_eco2_4_3DegreeOfUseOrTenancy";
			} break;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 :
			switch (t) {
				case 0 : return "DUTTCDUT_ResultsSubmitted";
			} break;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 :
			switch (t) {
				case 0 : return "DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy";
			} break;
			// Eco2_4_4::para_t
			case 16 :
			switch (t) {
				case 0 : return "CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace";
				case 1 : return "ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower";
				case 2 : return "ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper";
			} break;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 :
			switch (t) {
				case 0 : return "SERUSGS_ResultsSubmitted";
				case 1 : return "SERUSGS_LogisticsAndProductionCostOptimisation";
				case 2 : return "SERUSGS_LogisticsAndProductionEnvironmentalOptimisation";
				case 3 : return "SERUSGS_LogisticsAndProductionSocialOptimisation";
			} break;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 :
			switch (t) {
				case 0 : return "SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace";
				case 1 : return "SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace";
			} break;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 :
			switch (t) {
				case 0 : return "SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy";
			} break;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 :
			switch (t) {
				case 0 : return "RAAEF_RiskAnalysisDuringEarlyPlanningPhases";
			} break;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 :
			switch (t) {
				case 0 : return "RABCT_AspirationsForVerification";
				case 1 : return "RABCT_ImplementationOfStandards";
			} break;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 :
			switch (t) {
				case 0 : return "A2030CDI_QualityOfInternetConnection";
			} break;
			// Eco2_4_7::A2030_Expandability
			case 23 :
			switch (t) {
				case 0 : return "A2030E_Concept";
			} break;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 :
			switch (t) {
				case 0 : return "A2030IA_AddressEffect";
			} break;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 :
			switch (t) {
				case 0 : return "BCRMPVPrePH4_ConceptSubmitted";
			} break;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 :
			switch (t) {
				case 0 : return "BCRMPVPostPH4_ConceptSubmitted";
				case 1 : return "BCRMPVPostPH4_ProofOfNoNegativeConcequences";
			} break;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 :
			switch (t) {
				case 0 : return "A2030CBA_Evaluation";
			} break;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 :
			switch (t) {
				case 0 : return "ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented";
				case 1 : return "ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors";
				case 2 : return "ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors";
				case 3 : return "ACCQEM_MeasuresReduceProbableFutureRisksOnSite";
			} break;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 :
			switch (t) {
				case 0 : return "ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions";
				case 1 : return "ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans";
				case 2 : return "ACCQIAM_MeasuresInAccordanceWithNationalStrategy";
				case 3 : return "ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures";
				case 4 : return "ACCQIAM_RegulationOfRemedialMeasures";
			} break;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 :
			switch (t) {
				case 0 : return "ACCGRED_EssentialMeasuresTaken";
				case 1 : return "ACCGRED_GeneralResilienceExists";
			} break;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 :
			switch (t) {
				case 0 : return "ACCA2030HL_ProbableHighHeatLoad";
				case 1 : return "ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 :
			switch (t) {
				case 0 : return "MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity";
				case 1 : return "MAFERSCMAQ_RiskAnalysisConducted";
				case 2 : return "MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 :
			switch (t) {
				case 0 : return "MAFERSCMN_NoiseProtectionConstruction";
				case 1 : return "MAFERSCMN_InclusionOfNoiseProtectionGroundPlans";
				case 2 : return "MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures";
				case 3 : return "MAFERSCMN_OptimisationmeasuresImplemented";
			} break;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 :
			switch (t) {
				case 0 : return "MAFERSRRR_RadonAccessPreventedOrHeavilyHindered";
			} break;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 :
			switch (t) {
				case 0 : return "DCBCPD_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient";
				case 2 : return "DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding";
			} break;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 :
			switch (t) {
				case 0 : return "DCBCSBD_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData";
				case 2 : return "DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation";
				case 3 : return "DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding";
				case 4 : return "DCBCSBD_PartsCatalogueHandedOverToClient";
			} break;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 :
			switch (t) {
				case 0 : return "DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines";
			} break;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 :
			switch (t) {
				case 0 : return "DCBA2030DF_DigitalFootprintHeavilyReduced";
			} break;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 :
			switch (t) {
				case 0 : return "ODBUROMP_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient";
				case 2 : return "ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany";
			} break;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 :
			switch (t) {
				case 0 : return "ODBUOFBM_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany";
				case 2 : return "ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring";
			} break;
			// Eco2_7_3::PPBIM_Preparation
			case 41 :
			switch (t) {
				case 0 : return "PPBIMP_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "PPBIMP_UseOfSharedDataEnvironment";
				case 2 : return "PPBIMP_NecessaryBasicDocuments";
				case 3 : return "PPBIMP_BIMCoordinatorSurveilingModelQuality";
				case 4 : return "PPBIMP_CompetenceCheckAndCoordinationOfBEP";
				case 5 : return "PPBIMP_BIMInformationRequirementsAndGoalsCommunicated";
			} break;
			// Eco2_7_3::PPBIM_Creation
			case 42 :
			switch (t) {
				case 0 : return "PPBIMC_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "PPBIMC_Level0to1_CAD3D";
				case 2 : return "PPBIMC_Level2_BIM4to5D";
				case 3 : return "PPBIMC_Level3_IntegratedBIM6to7D";
			} break;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 :
			switch (t) {
				case 0 : return "PPBIMSO_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "PPBIMSO_VariantsCalculatedAndDocumented";
			} break;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 :
			switch (t) {
				case 0 : return "PPBIMCEBIM2FMOC_SustainableOperatorConcept";
			} break;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 :
			switch (t) {
				case 0 : return "PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted";
			} break;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 :
			switch (t) {
				case 0 : return "DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "DTOPCHDBM_AsBuiltControlImplementedAndDocumented";
				case 2 : return "DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality";
				case 3 : return "DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable";
			} break;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 :
			switch (t) {
				case 0 : return "DTOPCEDPC_DigitalisationConducted";
			} break;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 :
			switch (t) {
				case 0 : return "DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient";
			} break;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 :
			switch (t) {
				case 0 : return "ACCDT_CircularDigitalTwinImplemented";
			} break;
			// Economy::para_weights
			case 50 :
			switch (t) {
				case 0 : return "PW_Eco1_1";
				case 1 : return "PW_Eco2_4";
				case 2 : return "PW_Eco2_6";
				case 3 : return "PW_Eco2_7";
			} break;
			// Economy::para_goals
			case 51 :
			switch (t) {
				case 0 : return "PG_Eco1_1";
				case 1 : return "PG_Eco2_4";
				case 2 : return "PG_Eco2_6";
				case 3 : return "PG_Eco2_7";
			} break;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 :
			switch (t) {
				case 0 : return "CO2ESOE_HighEnergyStandard";
				case 1 : return "CO2ESOE_CO2NeutralOperation";
				case 2 : return "CO2ESOE_PreparedCO2NeutralOperation";
				case 3 : return "CO2ESOE_SufficiencyStandard";
			} break;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 :
			switch (t) {
				case 0 : return "CO2ESFV_MaterialOptimization";
				case 1 : return "CO2ESFV_CO2ReducedMaterials";
				case 2 : return "CO2ESFV_LowTech";
				case 3 : return "CO2ESFV_CircularDesign";
				case 4 : return "CO2ESFV_Longevity";
			} break;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 :
			switch (t) {
				case 0 : return "CO2PSOE_ElevatedEnergeticStandard";
				case 1 : return "CO2PSOE_NettoGreenhouseGasNeutralOperation";
				case 2 : return "CO2PSOE_SufficiencyStandard";
			} break;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 :
			switch (t) {
				case 0 : return "CO2PSFV_MaterialOptimization";
				case 1 : return "CO2PSFV_CO2ReducedMaterials";
				case 2 : return "CO2PSFV_LowTech";
				case 3 : return "CO2PSFV_CircularDesign";
				case 4 : return "CO2PSFV_Longevity";
			} break;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 :
			switch (t) {
				case 0 : return "CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission";
			} break;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 :
			switch (t) {
				case 0 : return "CO2A2030IPB_IntegrationOfPreexistingBuilding";
			} break;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 :
			switch (t) {
				case 0 : return "CO2A2030MO_ForEmission";
			} break;
			// Env1_1_2::para_t
			case 59 :
			switch (t) {
				case 0 : return "RefEnv1_1_2_2_1";
				case 1 : return "CurrentValueEnv1_1_2_2_1";
				case 2 : return "RefEnv1_1_2_5_1";
				case 3 : return "CurrentValueEnv1_1_2_5_1";
			} break;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 :
			switch (t) {
				case 0 : return "LCCO2Disc_GreenHouseGasBalance";
				case 1 : return "LCCO2Disc_NonRenewablePrimaryEnergyBalance";
			} break;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 :
			switch (t) {
				case 0 : return "LCCO2IER_ResultsSubmitted";
			} break;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 :
			switch (t) {
				case 0 : return "LCCO2A2030LCCPA_AgendaSubmitted";
			} break;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 :
			switch (t) {
				case 0 : return "LCCO2A2030CPTS_AgendaSubmitted";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 :
			switch (t) {
				case 0 : return "LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation";
				case 1 : return "LCCO2BFO_AmbitiousClimateProtectionAgenda";
				case 2 : return "LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 :
			switch (t) {
				case 0 : return "LCCO2BFSCO2RCP_ResultsSubmitted";
			} break;
			// Env1_1_3::para_t
			case 66 :
			switch (t) {
				case 0 : return "RefEnv1_1_3_1_1";
				case 1 : return "CurrentValueEnv1_1_3_1_1";
				case 2 : return "RefEnv1_1_3_1_2POCP";
				case 3 : return "CurrentValueEnv1_1_3_1_2POCP";
				case 4 : return "RefEnv1_1_3_1_2AP";
				case 5 : return "CurrentValueEnv1_1_3_1_2AP";
				case 6 : return "RefEnv1_1_3_1_2EP";
				case 7 : return "CurrentValueEnv1_1_3_1_2EP";
				case 8 : return "RefEnv1_1_3_1_2FW";
				case 9 : return "CurrentValueEnv1_1_3_1_2FW";
			} break;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 :
			switch (t) {
				case 0 : return "CVAEILCPEB_ResultsSubmitted";
			} break;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 :
			switch (t) {
				case 0 : return "CVAEIWRAEI_ResultsSubmitted";
			} break;
			// Env1_2_1::para_t
			case 69 :
			switch (t) {
				case 0 : return "EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows";
				case 1 : return "EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows";
			} break;
			// Env1_2_1::EFM_A
			case 70 :
			switch (t) {
				case 0 : return "EFMA_QS1SimplifiedDocumentation";
				case 1 : return "EFMA_QS2SimplifiedDocumentation";
				case 2 : return "EFMA_QS2MaterialEcologicalComponentCatalogue";
				case 3 : return "EFMA_QS3MaterialEcologicalComponentCatalogue";
				case 4 : return "EFMA_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 :
			switch (t) {
				case 0 : return "EFMBRC_QS1SimplifiedDocumentation";
				case 1 : return "EFMBRC_QS2SimplifiedDocumentation";
				case 2 : return "EFMBRC_QS2MaterialEcologicalComponentCatalogue";
				case 3 : return "EFMBRC_QS3MaterialEcologicalComponentCatalogue";
				case 4 : return "EFMBRC_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 :
			switch (t) {
				case 0 : return "EFMBSC_QS1SimplifiedDocumentation";
				case 1 : return "EFMBSC_QS2SimplifiedDocumentation";
				case 2 : return "EFMBSC_QS2MaterialEcologicalComponentCatalogue";
				case 3 : return "EFMBSC_QS3MaterialEcologicalComponentCatalogue";
				case 4 : return "EFMBSC_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_Agenda2030
			case 73 :
			switch (t) {
				case 0 : return "EFMA2030_1WaivingOfCrossOutCriterionQS3";
				case 1 : return "EFMA2030_2WaivingOfCrossOutCriterionQS4";
				case 2 : return "EFMA2030_MeasurementsTakenForSufficientStructure";
				case 3 : return "EFMA2030_WaivingOfUnsolveableConnections";
				case 4 : return "EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent";
			} break;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 :
			switch (t) {
				case 0 : return "EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent";
			} break;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 :
			switch (t) {
				case 0 : return "RURPESCD_DeclarationOfDiligenceGiven";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 :
			switch (t) {
				case 0 : return "RURPERURP_RegularIntegrationOfMeasures";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 :
			switch (t) {
				case 0 : return "RURPERURED_PartsCatalogue";
			} break;
			// Env1_3_2::para_t
			case 78 :
			switch (t) {
				case 0 : return "Env1_3_2_1NumberOfPartsFromDiffManufacturers";
				case 1 : return "ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup";
				case 2 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4";
				case 3 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2";
				case 4 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4";
				case 5 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2";
			} break;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 :
			switch (t) {
				case 0 : return "RRMCRRM_ResultSumbitted";
			} break;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 :
			switch (t) {
				case 0 : return "RRMRRWPSR_DetailedMethod";
				case 1 : return "RRMRRWPSR_SimplifiedMethod";
			} break;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 :
			switch (t) {
				case 0 : return "RRMPWMSF_PercentageMinimum50";
			} break;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 :
			switch (t) {
				case 0 : return "RRMPRCEWMPS_Percentage";
			} break;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 :
			switch (t) {
				case 0 : return "DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage";
				case 1 : return "DWDWWVSCWU_FlowClassesOfSanitaryEquipment";
				case 2 : return "DWDWWVSCWU_LocalWaterUsageIndex";
				case 3 : return "DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage";
				case 4 : return "DWDWWVSCWU_EfficentWateringOfOutsideAreas";
				case 5 : return "DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint";
			} break;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 :
			switch (t) {
				case 0 : return "DWDWWVUSC_ConceptUpdatedToPlanningProgress";
				case 1 : return "DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects";
			} break;
			// Env2_2_2::para_t
			case 85 :
			switch (t) {
				case 0 : return "CurrentValue_env2_2WaterUsageIndex";
				case 1 : return "RefValue_env2_2DWDWWVWUI_DynamicThreshold";
			} break;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 :
			switch (t) {
				case 0 : return "DWDWWVWUI_ResultsSubmitted";
			} break;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 :
			switch (t) {
				case 0 : return "DWDWWVIR_NoPlannedIrrigationWithDrinkingWater";
				case 1 : return "DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup";
			} break;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 :
			switch (t) {
				case 0 : return "DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc";
			} break;
			// Env2_2_5::para_t
			case 89 :
			switch (t) {
				case 0 : return "CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation";
				case 1 : return "CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion";
				case 2 : return "CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion";
			} break;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 :
			switch (t) {
				case 0 : return "DWDWWVSC_ResultsSubmitted";
				case 1 : return "DWDWWVSC_InfiltrationPossible";
				case 2 : return "DWDWWVSC_UndercuttingTheDrainagePortion";
			} break;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 :
			switch (t) {
				case 0 : return "DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem";
				case 1 : return "DWDWWVDWS_ObservationOfDrinkingWaterSanitation";
				case 2 : return "DWDWWVDWS_WarmWaterReducedToOperativeMinimum";
				case 3 : return "DWDWWVDWS_ColdWaterLessThan20Degrees";
			} break;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 :
			switch (t) {
				case 0 : return "ADDC_OutlyingDevelopmentArea";
				case 1 : return "ADDC_InternalDevelopmentArea";
				case 2 : return "ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse";
			} break;
			// Env2_3_2::para_t
			case 93 :
			switch (t) {
				case 0 : return "CurrentValue_env2_3_2ADDSAM_DegreeOfSealing";
			} break;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 :
			switch (t) {
				case 0 : return "ADDSAM_ResultsSubmitted";
				case 1 : return "ADDSAM_ImplementationOfAdjustmentMeasures";
			} break;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 :
			switch (t) {
				case 0 : return "ADCEBU_30PercentOfAreaUnsealedPreConstruction";
			} break;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 :
			switch (t) {
				case 0 : return "ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination";
				case 1 : return "ADSQISR_LowContaminationRecyclingAndDisposal";
				case 2 : return "ADSQISR_HighContaminationDisposal";
			} break;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 :
			switch (t) {
				case 0 : return "ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange";
				case 1 : return "ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants";
				case 2 : return "ADSQICEBISSRS_RestorationOfGroundWaterDamages";
			} break;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 :
			switch (t) {
				case 0 : return "BDOSCEBDS_ExtensiveAndLongTermStrategy";
			} break;
			// Env2_4_2::para_t
			case 99 :
			switch (t) {
				case 0 : return "CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea";
				case 1 : return "CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof";
				case 2 : return "CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite";
			} break;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 :
			switch (t) {
				case 0 : return "BDOSBBSA_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 :
			switch (t) {
				case 0 : return "BDOSBGR_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 :
			switch (t) {
				case 0 : return "BDOSBAFA2030VB_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 :
			switch (t) {
				case 0 : return "BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept";
				case 1 : return "BDOSDS_TwoBiotopeStructureTypesAvailable";
			} break;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 :
			switch (t) {
				case 0 : return "BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus";
			} break;
			// Env2_4_3::para_t
			case 105 :
			switch (t) {
				case 0 : return "CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult";
			} break;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 :
			switch (t) {
				case 0 : return "BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies";
				case 1 : return "BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies";
			} break;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 :
			switch (t) {
				case 0 : return "BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept";
				case 1 : return "BDOSVEDLSSS_ResultSubmitted";
			} break;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 :
			switch (t) {
				case 0 : return "BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter";
			} break;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 :
			switch (t) {
				case 0 : return "BDOSRSBI_ConceptDeveloped";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 :
			switch (t) {
				case 0 : return "BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution";
				case 1 : return "BDOSRNIIC_HarmlessLightSourceOrientation";
				case 2 : return "BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature";
				case 3 : return "BDOSRNIIC_NoUnwantedBlindingEffects";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 :
			switch (t) {
				case 0 : return "BDOSRNIAT_EvaluationOfDangersToAnimals";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 :
			switch (t) {
				case 0 : return "BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 :
			switch (t) {
				case 0 : return "BDOSPCMDMCC_ContractSubmitted";
				case 1 : return "BDOSPCMDMCC_EcologicalCarePlanSubmitted";
				case 2 : return "BDOSPCMDMCC_NoUseOfTurfMaterials";
				case 3 : return "BDOSPCMDMCC_NoUseOfHerbicidesOnSite";
				case 4 : return "BDOSPCMDMCC_NoUseOfBiocidesOnSite";
				case 5 : return "BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 :
			switch (t) {
				case 0 : return "BDOSPCMMSC_SimpleMonitoringOfNestingAids";
				case 1 : return "BDOSPCMMSC_ExtensiveMonitoring";
			} break;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 :
			switch (t) {
				case 0 : return "BDOSAC_AlternativeCertificationSubmitted";
			} break;
			// Environment::para_weights
			case 116 :
			switch (t) {
				case 0 : return "PW_Env1_1";
				case 1 : return "PW_Env1_2";
				case 2 : return "PW_Env1_3";
				case 3 : return "PW_Env2_2";
				case 4 : return "PW_Env2_3";
				case 5 : return "PW_Env2_4";
			} break;
			// Environment::para_goals
			case 117 :
			switch (t) {
				case 0 : return "PG_Env1_1";
				case 1 : return "PG_Env1_2";
				case 2 : return "PG_Env1_3";
				case 3 : return "PG_Env2_2";
				case 4 : return "PG_Env2_3";
				case 5 : return "PG_Env2_4";
			} break;
			// KeywordList::MyParameters
			case 118 :
			switch (t) {
				case 0 : return "Temperature";
				case 1 : return "Mass";
			} break;
			// Pro1_1_1::RP_Basis
			case 119 :
			switch (t) {
				case 0 : return "RPB_ImplementationOfDeclarationSustainabilityArchitecture";
				case 1 : return "RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels";
			} break;
			// Pro1_1_1::RP_RP
			case 120 :
			switch (t) {
				case 0 : return "RPRP_PlanFollowsChecklist1OrAnnexe1A";
				case 1 : return "RPRP_PlanFollowsChecklist12OrAnnexe1B";
				case 2 : return "RPRP_PlanFollowsChecklist123OrAnnexe1C";
			} break;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 :
			switch (t) {
				case 0 : return "RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts";
			} break;
			// Pro1_1_2::A2030_Participation
			case 122 :
			switch (t) {
				case 0 : return "A2030P_CounselDuringRequirementAnalysis";
				case 1 : return "A2030P_ParticipationDuringRequirementAnalysis";
				case 2 : return "A2030P_CounselDuringConceptionPhase";
				case 3 : return "A2030P_ParticipationDuringConceptionPhase";
				case 4 : return "A2030P_CounselDuringImplementationPhase";
				case 5 : return "A2030P_ParticipationDuringImplementationPhase";
			} break;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 :
			switch (t) {
				case 0 : return "CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase";
				case 1 : return "CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam";
			} break;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 :
			switch (t) {
				case 0 : return "SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks";
				case 1 : return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks";
				case 2 : return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer";
				case 3 : return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer";
			} break;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 :
			switch (t) {
				case 0 : return "SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer";
			} break;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 :
			switch (t) {
				case 0 : return "CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 :
			switch (t) {
				case 0 : return "CEVCAMSM_ImplementationOfConceptAssignment";
				case 1 : return "CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 :
			switch (t) {
				case 0 : return "CEVCAQE_CompetentDecisionMakingBoard";
				case 1 : return "CEVCAQE_PostProcedureQualityEnsurance";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 :
			switch (t) {
				case 0 : return "CEVMASM_ImplementationOfMultipleAssignments";
				case 1 : return "CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 :
			switch (t) {
				case 0 : return "CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 :
			switch (t) {
				case 0 : return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3";
				case 1 : return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5";
				case 2 : return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 :
			switch (t) {
				case 0 : return "CEVPCSQM_ImplementationOfPlanningCompetition";
				case 1 : return "CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 :
			switch (t) {
				case 0 : return "CEVPCMCM_CooperativeMethod";
				case 1 : return "CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 :
			switch (t) {
				case 0 : return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3";
				case 1 : return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5";
				case 2 : return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 :
			switch (t) {
				case 0 : return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3";
				case 1 : return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5";
				case 2 : return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 :
			switch (t) {
				case 0 : return "RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation";
				case 1 : return "RIDB_ImplementationOfDesignBoardsRecommendations";
			} break;
			// Pro1_6_3::HAA_Recognition
			case 137 :
			switch (t) {
				case 0 : return "HAAR_RecognitionOfGoodConstructionalCulturalQuality";
				case 1 : return "HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond";
			} break;
			// Pro2_1_1::NRCS_Concept
			case 138 :
			switch (t) {
				case 0 : return "NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 :
			switch (t) {
				case 0 : return "NRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 :
			switch (t) {
				case 0 : return "NRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_2::DRCS_Concept
			case 141 :
			switch (t) {
				case 0 : return "DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 :
			switch (t) {
				case 0 : return "DRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 :
			switch (t) {
				case 0 : return "DRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_3::SGPCS_Concept
			case 144 :
			switch (t) {
				case 0 : return "SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 :
			switch (t) {
				case 0 : return "SGPCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 :
			switch (t) {
				case 0 : return "SGPCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_4::WRCS_Concept
			case 147 :
			switch (t) {
				case 0 : return "WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 :
			switch (t) {
				case 0 : return "WRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 :
			switch (t) {
				case 0 : return "WRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 :
			switch (t) {
				case 0 : return "WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies";
			} break;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 :
			switch (t) {
				case 0 : return "CESI_NotificationOfNearbyResidentsOnProjectAndSite";
			} break;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 :
			switch (t) {
				case 0 : return "CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage";
			} break;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 :
			switch (t) {
				case 0 : return "CISI_ParticipantsInProjectProvidedWithAllRelevantInformation";
				case 1 : return "CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite";
				case 2 : return "CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress";
				case 3 : return "CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors";
				case 4 : return "CISI_OnlineAvailabilityOfAllInformation";
			} break;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 :
			switch (t) {
				case 0 : return "RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite";
			} break;
			// Pro2_1_6::RCWU_Concept
			case 155 :
			switch (t) {
				case 0 : return "RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 :
			switch (t) {
				case 0 : return "RCWUIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 :
			switch (t) {
				case 0 : return "RCWUEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 :
			switch (t) {
				case 0 : return "RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite";
			} break;
			// Pro2_1_6::RCEU_Concept
			case 159 :
			switch (t) {
				case 0 : return "RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 :
			switch (t) {
				case 0 : return "RCEUIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 :
			switch (t) {
				case 0 : return "RCEUEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_7::M_Prevention
			case 162 :
			switch (t) {
				case 0 : return "MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite";
			} break;
			// Pro2_3_1::TM_PlanningPhase
			case 163 :
			switch (t) {
				case 0 : return "TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring";
				case 1 : return "TMPP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 :
			switch (t) {
				case 0 : return "TMCP_ContinuationOfAMonitoringConcept";
				case 1 : return "TMCP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_3::TrialOperation
			case 165 :
			switch (t) {
				case 0 : return "TO_TrialOperationConductedPriorToApprovalAndHandover";
				case 1 : return "TO_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 :
			switch (t) {
				case 0 : return "TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation";
				case 1 : return "TMFOP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 :
			switch (t) {
				case 0 : return "TMCM_AssignmentOfACompleteTechnicalMonitoring";
			} break;
			// Pro2_3_6::OperationStartUpManagement
			case 168 :
			switch (t) {
				case 0 : return "OSUM_StartUpManagementInAdditionToTechnicalManagement";
			} break;
			// Pro2_3_7::BuildingPerformance
			case 169 :
			switch (t) {
				case 0 : return "BP_AssignmentOfContinuousImprovementProcessAfterHandover";
			} break;
			// Pro2_5_1::FM_Check
			case 170 :
			switch (t) {
				case 0 : return "FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage";
			} break;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 :
			switch (t) {
				case 0 : return "MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors";
				case 1 : return "MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400";
				case 2 : return "MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation";
			} break;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 :
			switch (t) {
				case 0 : return "FMG_CreationAndHandoverToFacilityManager";
			} break;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 :
			switch (t) {
				case 0 : return "CWU_CreationAndHandoverTechnicalOperationHandbook";
				case 1 : return "CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase";
			} break;
			// Pro2_5_5::SIS_Implementation
			case 174 :
			switch (t) {
				case 0 : return "SISI_CreationOfConceptIncludingImplementationPlan";
				case 1 : return "SISI_InstallationOfSustainabilityInformationSystem";
			} break;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 :
			switch (t) {
				case 0 : return "SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept";
				case 1 : return "SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses";
			} break;
			// Pro2_5_6::OCP_Extended
			case 176 :
			switch (t) {
				case 0 : return "OCPE_CreationOfExtendedOperationCostPrognosis";
			} break;
			// Process::para_weights
			case 177 :
			switch (t) {
				case 0 : return "PW_Pro1_1";
				case 1 : return "PW_Pro1_4";
				case 2 : return "PW_Pro1_6";
				case 3 : return "PW_Pro2_1";
				case 4 : return "PW_Pro2_3";
				case 5 : return "PW_Pro2_5";
			} break;
			// Process::para_goals
			case 178 :
			switch (t) {
				case 0 : return "PG_Pro1_1";
				case 1 : return "PG_Pro1_4";
				case 2 : return "PG_Pro1_6";
				case 3 : return "PG_Pro2_1";
				case 4 : return "PG_Pro2_3";
				case 5 : return "PG_Pro2_5";
			} break;
			// Site::para_weights
			case 179 :
			switch (t) {
				case 0 : return "PW_Site1_1";
				case 1 : return "PW_Site1_3";
				case 2 : return "PW_Site1_4";
			} break;
			// Site::para_goals
			case 180 :
			switch (t) {
				case 0 : return "PG_Site1_1";
				case 1 : return "PG_Site1_3";
				case 2 : return "PG_Site1_4";
			} break;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 :
			switch (t) {
				case 0 : return "CRCA_ConductionOfAnalysis";
				case 1 : return "CRCA_ConductionOfQualifiedAnalysisByExperts";
			} break;
			// Site1_1_1::CR_Screening
			case 182 :
			switch (t) {
				case 0 : return "CRS_AppendixA3TableA";
				case 1 : return "CRS_AppendixA3TableB";
				case 2 : return "CRS_AdditionallyAppendixA3TableC";
			} break;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 :
			switch (t) {
				case 0 : return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years";
				case 1 : return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years";
				case 2 : return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy";
			} break;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 :
			switch (t) {
				case 0 : return "CRAT_EvaluationOfEnvironmentAndClimateHazardProbability";
				case 1 : return "CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue";
			} break;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 :
			switch (t) {
				case 0 : return "CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers";
			} break;
			// Site1_1_1::CR_DataBasis
			case 186 :
			switch (t) {
				case 0 : return "CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85";
				case 1 : return "CRDB_AdditionallyScenarioRCP6_0";
				case 2 : return "CRDB_AdditionallyScenarioRCP4_5";
				case 3 : return "CRDB_AdditionallyScenarioRCP2_6";
			} break;
			// Site1_1_1::CR_ResultApplication
			case 187 :
			switch (t) {
				case 0 : return "CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction";
			} break;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 :
			switch (t) {
				case 0 : return "ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue";
			} break;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 :
			switch (t) {
				case 0 : return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB";
				case 1 : return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB";
				case 2 : return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB";
			} break;
			// Site1_1_3::EEI_AirQuality
			case 190 :
			switch (t) {
				case 0 : return "EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually";
				case 1 : return "EEIAQ_PM10NeverExceedsLimit";
				case 2 : return "EEIAQ_PM2_5NeverExceedsLimit";
				case 3 : return "EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually";
				case 4 : return "EEIAQ_NO2NeverExceedsExceedsLimit";
			} break;
			// Site1_1_3::EEI_Radon
			case 191 :
			switch (t) {
				case 0 : return "EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation";
				case 1 : return "EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation";
				case 2 : return "EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured";
				case 3 : return "EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings";
			} break;
			// Site1_3_1::MIT_Surroundings
			case 192 :
			switch (t) {
				case 0 : return "MITS_ConnectionToBundesstrasseA_Road";
				case 1 : return "MITS_ConnectionToFreeway";
				case 2 : return "MITS_ConnectionToMainStreet";
			} break;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 :
			switch (t) {
				case 0 : return "MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter";
			} break;
			// Site1_3_2::PT_Stations
			case 194 :
			switch (t) {
				case 0 : return "PTS_DistancedWithin350Meters";
			} break;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 :
			switch (t) {
				case 0 : return "PTDTSHD_NoMoreThan20Minutes";
				case 1 : return "PTDTSHD_NoMoreThan15Minutes";
				case 2 : return "PTDTSHD_NoMoreThan10Minutes";
			} break;
			// Site1_3_2::PT_Intervals
			case 196 :
			switch (t) {
				case 0 : return "PTI_NoMoreThan15Minutes";
				case 1 : return "PTI_NoMoreThan10Minutes";
				case 2 : return "PTI_NoMoreThan5Minutes";
			} break;
			// Site1_3_2::PT_RelationToBuilding
			case 197 :
			switch (t) {
				case 0 : return "PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay";
				case 1 : return "PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances";
				case 2 : return "PTRB_BuildingFeaturesSignageToStations";
			} break;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 :
			switch (t) {
				case 0 : return "BTCT500M_PartialMixWithMotorTraffic";
				case 1 : return "BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks";
			} break;
			// Site1_3_3::BT_Connection
			case 199 :
			switch (t) {
				case 0 : return "BTC_ContinuousRegionalConnection";
				case 1 : return "BTC_ContinuousInterregionalConnectionMoreThan10KM";
			} break;
			// Site1_3_3::BT_RelationToBuilding
			case 200 :
			switch (t) {
				case 0 : return "BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks";
			} break;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 :
			switch (t) {
				case 0 : return "FTWN350M_50PercentOrMoreCoverage";
				case 1 : return "FTWN350M_80PercentOrMoreCoverage";
				case 2 : return "FTWN350M_100PercentCoverage";
			} break;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 :
			switch (t) {
				case 0 : return "FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach";
				case 1 : return "FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach";
			} break;
			// Site1_3_4::FT_SignageSystems
			case 203 :
			switch (t) {
				case 0 : return "FTSS_SignageCoversSurroundingArea";
				case 1 : return "FTSS_SignageAndOrientationPlansCoverSurroundingArea";
			} break;
			// Site1_3_5::AS_Within350Meters
			case 204 :
			switch (t) {
				case 0 : return "ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots";
				case 1 : return "ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots";
			} break;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 :
			switch (t) {
				case 0 : return "ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs";
			} break;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 :
			switch (t) {
				case 0 : return "A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters";
			} break;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 :
			switch (t) {
				case 0 : return "SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters";
				case 1 : return "SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters";
				case 2 : return "SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 3 : return "SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 4 : return "SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 5 : return "SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 6 : return "SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 7 : return "SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 8 : return "SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 9 : return "SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers";
				case 10 : return "SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters";
				case 11 : return "SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
			} break;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 :
			switch (t) {
				case 0 : return "SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily";
				case 1 : return "SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours";
				case 2 : return "SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes";
			} break;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 :
			switch (t) {
				case 0 : return "POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 1 : return "POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 2 : return "POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 3 : return "POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 4 : return "POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 5 : return "POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 6 : return "POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
			} break;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 :
			switch (t) {
				case 0 : return "BAIUDIHD_Daycare";
				case 1 : return "BAIUDIHD_SecondaryOrVocationalSchool";
				case 2 : return "BAIUDIHD_CinemaTheatreOrGallery";
				case 3 : return "BAIUDIHD_Bookstore";
				case 4 : return "BAIUDIHD_QuarterCenter";
				case 5 : return "BAIUDIHD_ParishHall";
				case 6 : return "BAIUDIHD_YouthCenter";
				case 7 : return "BAIUDIHD_ElderlyCenter";
				case 8 : return "BAIUDIHD_FitnessCenter";
				case 9 : return "BAIUDIHD_FitnessProgramOpenToExternalUsers";
				case 10 : return "BAIUDIHD_Playground";
				case 11 : return "BAIUDIHD_GymSportsFieldOrSwimmingPool";
				case 12 : return "BAIUDIHD_LocalAmeneties1_ShoppingCenter";
				case 13 : return "BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc";
				case 14 : return "BAIUDIHD_LocalAmeneties3_FarmersMarket";
				case 15 : return "BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc";
				case 16 : return "BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter";
				case 17 : return "BAIUDIHD_Healthcare1_GeneralPractitioner";
				case 18 : return "BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc";
			} break;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 :
			switch (t) {
				case 0 : return "BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals";
				case 1 : return "BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers";
			} break;
			// Soc1_1_1::para_t
			case 212 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad";
			} break;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 :
			switch (t) {
				case 0 : return "OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3";
				case 1 : return "OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2";
				case 2 : return "OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification";
				case 3 : return "OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3";
				case 4 : return "OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2";
				case 5 : return "OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees";
				case 6 : return "OTRTOT_LogisticsAndProductionLimitationTo30Degrees";
			} break;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 :
			switch (t) {
				case 0 : return "RHHP_RelativeHumidityHigherThan30Percent";
				case 1 : return "RHHP_HotelRelativeHumidityLowerThan70Percent";
				case 2 : return "RHHP_ConditionMetFor95PercentOfTime";
			} break;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 :
			switch (t) {
				case 0 : return "RHCP_MaxHumidity12GramPerKilogram";
			} break;
			// Soc1_1_3::D_CoolingPeriod
			case 216 :
			switch (t) {
				case 0 : return "DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB";
				case 1 : return "DCP_ShoppingCenterPreventionOfDraught";
			} break;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 :
			switch (t) {
				case 0 : return "RTAFTCP_CeilingMin16Degrees";
				case 1 : return "RTAFTCP_CeilingMax35Degrees";
				case 2 : return "RTAFTCP_GlassSurfacesMin18Degrees";
				case 3 : return "RTAFTCP_GlassSurfacesMax35Degrees";
				case 4 : return "RTAFTCP_FloorMin19Degrees";
				case 5 : return "RTAFTCP_FloorMax29Degrees";
				case 6 : return "RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA";
			} break;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 :
			switch (t) {
				case 0 : return "A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture";
				case 1 : return "A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess";
			} break;
			// Soc1_1_6::UI_UserInfluence
			case 219 :
			switch (t) {
				case 0 : return "UI_PossibilityOfReuse";
				case 1 : return "UI_RoomAirCycleIndividuallyManipulable";
				case 2 : return "UI_RoomTemperatureIndividuallyManipulable";
				case 3 : return "UI_SurveyOnUserSatisfactionAndEnergyEfficiency";
			} break;
			// Soc1_1_Alt::AC_Innovation
			case 220 :
			switch (t) {
				case 0 : return "AC_AlternativeCertificationForIndicators1to4";
			} break;
			// Soc1_2_1::para_t
			case 221 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_2_TVOC";
				case 1 : return "CurrentValue_soc1_2_Formaldehyde";
				case 2 : return "CurrentValue_soc1_2_TVOCRenterPromise";
				case 3 : return "CurrentValue_soc1_2_FormaldehydeRenterPromise";
			} break;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 :
			switch (t) {
				case 0 : return "IHTVOCM_TVOCResultsSubmitted";
				case 1 : return "IHTVOCM_FormaldehydeResultsSubmitted";
				case 2 : return "IHTVOCM_AlternativeCertification";
				case 3 : return "IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent";
				case 4 : return "IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors";
				case 5 : return "IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces";
			} break;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 :
			switch (t) {
				case 0 : return "IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed";
				case 1 : return "IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces";
				case 2 : return "IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces";
			} break;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 :
			switch (t) {
				case 0 : return "IHTVOCA2030IATMRHC_NonSmokerProtection";
				case 1 : return "IHTVOCA2030IATMRHC_RespirableDustPrevention";
			} break;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 :
			switch (t) {
				case 0 : return "IHTVOCWWB_WoodworkApplicable";
				case 1 : return "IHTVOCWWB_LimoneneBelowNOW";
				case 2 : return "IHTVOCWWB_AlphaPineneBelowNOW";
			} break;
			// Soc1_2_2::para_t
			case 226 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration";
				case 1 : return "CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 :
			switch (t) {
				case 0 : return "IHACFOEHAH_RatioSubmitted";
				case 1 : return "IHACFOEHAH_ZonalStreamingSimulation";
				case 2 : return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3";
				case 3 : return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2";
				case 4 : return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1";
				case 5 : return "IHACFOEHAH_ManualNoCertification";
				case 6 : return "IHACFOEHAH_ManualObservationOfASR3_6";
				case 7 : return "IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring";
				case 8 : return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4";
				case 9 : return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3";
				case 10 : return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 :
			switch (t) {
				case 0 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops";
				case 1 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops";
				case 2 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops";
				case 3 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls";
				case 4 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls";
				case 5 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 :
			switch (t) {
				case 0 : return "IHACFR_AerationMeasuresAccordingToLevelsFL";
				case 1 : return "IHACFR_AerationMeasuresAccordingToLevelsRL";
				case 2 : return "IHACFR_AerationMeasuresAccordingToLevelsNL";
			} break;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 :
			switch (t) {
				case 0 : return "IHACFLP_NoCertification";
				case 1 : return "IHACFLP_ObservationOfASR3_6";
				case 2 : return "IHACFLP_NeedbasedAeration";
				case 3 : return "IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent";
			} break;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 :
			switch (t) {
				case 0 : return "ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet";
			} break;
			// Soc1_3_1::ORSR_Office
			case 232 :
			switch (t) {
				case 0 : return "ORSRO_ObservationOfVDI_2569_ClassAorBRequirements";
			} break;
			// Soc1_3_1::ORSR_Residential
			case 233 :
			switch (t) {
				case 0 : return "ORSRR_DIN_4109_5_RequirementsMet";
				case 1 : return "ORSRR_SoundproofingPassClassCOrBetter";
			} break;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 :
			switch (t) {
				case 0 : return "BAMOEHAHcR_ConfirmationThroughMeasuring";
			} break;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 :
			switch (t) {
				case 0 : return "PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept";
			} break;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 :
			switch (t) {
				case 0 : return "RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB";
				case 1 : return "RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse";
				case 2 : return "RAHHcAEO_ObservationOfVDI_2569ClassA";
				case 3 : return "RAHHcAEO_ObservationOfVDI_2569ClassB";
				case 4 : return "RAHHcAEO_MeasuresTakenAndVerified";
			} break;
			// Soc1_3_3::RA_Residential
			case 237 :
			switch (t) {
				case 0 : return "RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways";
				case 1 : return "RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms";
			} break;
			// Soc1_4_1::para_t
			case 238 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_1ET";
				case 1 : return "CurrentValue_soc1_4_1D";
				case 2 : return "CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea";
			} break;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 :
			switch (t) {
				case 0 : return "DSOEARHHcP_ResultsSubmitted";
				case 1 : return "DSOEARHHcP_HotelAlternativeCertification";
			} break;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 :
			switch (t) {
				case 0 : return "DSOCSSCCB_ResultsSubmitted";
				case 1 : return "DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight";
			} break;
			// Soc1_4_2::para_t
			case 241 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_2UsageLighting";
				case 1 : return "CurrentValue_soc1_4_2TranslucentCeilingLightPortion";
			} break;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 :
			switch (t) {
				case 0 : return "ARULOEALHc_UsageLightingResultsSubmitted";
				case 1 : return "ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted";
				case 2 : return "ARULOEALHc_AssemblyAreaType1";
				case 3 : return "ARULOEALHc_AssemblyAreaType2";
			} break;
			// Soc1_4_3::para_t
			case 243 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_3_1aPercentageOfOpenFacade";
				case 1 : return "CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside";
			} break;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 :
			switch (t) {
				case 0 : return "LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms";
				case 1 : return "LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted";
				case 2 : return "LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS";
				case 3 : return "LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted";
				case 4 : return "LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS";
			} break;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 :
			switch (t) {
				case 0 : return "LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility";
				case 1 : return "LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility";
				case 2 : return "LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility";
				case 3 : return "LOSOOEHLARHc_RHHc_AlternativeRequirementsMet";
				case 4 : return "LOSOOEHLARHc_AssemblyType1";
				case 5 : return "LOSOOEHLARHc_AssemblyType2";
				case 6 : return "LOSOOEHLARHc_AnyDaylightInCommonAreas";
				case 7 : return "LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility";
				case 8 : return "LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility";
			} break;
			// Soc1_4_4::para_t
			case 246 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_4_1DaylightGlareProbability";
			} break;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 :
			switch (t) {
				case 0 : return "DGSOEA12Hc_DGPResultsSubmitted";
				case 1 : return "DGSOEA12Hc_AssemblyType1";
				case 2 : return "DGSOEA12Hc_AssemblyType2";
				case 3 : return "DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields";
				case 4 : return "DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights";
			} break;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 :
			switch (t) {
				case 0 : return "DGSCS_ObservationOfASRA3_4Chapter4_2";
			} break;
			// Soc1_4_4::DGS_Logistics
			case 249 :
			switch (t) {
				case 0 : return "DGSL_UncertifiedGlareShieldSystem";
				case 1 : return "DGSL_Class2GlareShieldSystem";
				case 2 : return "DGSL_Class3OrHigherGlareShieldSystem";
			} break;
			// Soc1_4_4::DGS_Production
			case 250 :
			switch (t) {
				case 0 : return "DGSP_CombinationOfLightDivertingSystemsAndGlareShields";
				case 1 : return "DGSP_UseOfHighNorthLightDiffusionCeilingLights";
			} break;
			// Soc1_4_5::AL_LightingConcept
			case 251 :
			switch (t) {
				case 0 : return "ALLC_CreationOfLightingConcept";
			} break;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 :
			switch (t) {
				case 0 : return "ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet";
				case 1 : return "ALIPCOR_AtLeastTwoOptimisationMeasuresTaken";
				case 2 : return "ALIPCOR_AdditionalOptimisationMeasuresTaken";
			} break;
			// Soc1_4_6::SED_Residential
			case 253 :
			switch (t) {
				case 0 : return "SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit";
				case 1 : return "SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit";
				case 2 : return "SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit";
			} break;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 :
			switch (t) {
				case 0 : return "SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms";
				case 1 : return "SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms";
				case 2 : return "SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent";
				case 3 : return "SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent";
			} break;
			// Soc1_6_1::para_t
			case 255 :
			switch (t) {
				case 0 : return "AlternativeInnovativeCommunicationConstellations";
			} break;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 :
			switch (t) {
				case 0 : return "CSOCZMU_DifferentCommunicationZones";
				case 1 : return "CSOCZMU_CommunicationSupportingRoomDesign";
				case 2 : return "CSOCZMU_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_2::para_t
			case 257 :
			switch (t) {
				case 0 : return "Soc1_6_2_1AlternativeInnovativeSolutions";
				case 1 : return "Soc1_6_2_2AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 :
			switch (t) {
				case 0 : return "AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms";
				case 1 : return "AOUAOS_CSCBSC_LockersChangingRooms";
				case 2 : return "AOUAOS_Residential_CommonRoomsAvailableToEveryone";
				case 3 : return "AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits";
				case 4 : return "AOUAOS_Hc_AdditionalOffersAvailableToEveryone";
				case 5 : return "AOUAOS_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 :
			switch (t) {
				case 0 : return "AOUOI_Signage";
				case 1 : return "AOUOI_InformationDesk";
				case 2 : return "AOUOI_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_3::para_t
			case 260 :
			switch (t) {
				case 0 : return "Soc1_6_3_1AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 :
			switch (t) {
				case 0 : return "FCEFOSO_Daycare";
				case 1 : return "FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms";
				case 2 : return "FCEFOSO_Playground";
				case 3 : return "FCEFOSO_ElderlyCommonRoomsPlayrooms";
				case 4 : return "FCEFOSO_FamilyFriendlyParking";
				case 5 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange";
				case 6 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib";
				case 7 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette";
				case 8 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind";
				case 9 : return "FCEFOSO_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_4::para_t
			case 262 :
			switch (t) {
				case 0 : return "Soc1_6_4_1AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 :
			switch (t) {
				case 0 : return "QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication";
				case 1 : return "QSIAA_DaylightAvailabilityInAllotmentAreas";
				case 2 : return "QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria";
				case 3 : return "QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse";
				case 4 : return "QSIAA_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::para_t
			case 264 :
			switch (t) {
				case 0 : return "Soc1_6_5_3AlternativeInnovativeSolutions";
				case 1 : return "Soc1_6_5_4AlternativeInnovativePoints";
			} break;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 :
			switch (t) {
				case 0 : return "QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions";
				case 1 : return "QSDCOA_DesignConsidersMaterialQuality";
				case 2 : return "QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting";
				case 3 : return "QSDCOA_DesignConsidersIntuitiveOrientation";
				case 4 : return "QSDCOA_DesignAvoidsPlacesOfAnxiety";
				case 5 : return "QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities";
				case 6 : return "QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents";
				case 7 : return "QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 :
			switch (t) {
				case 0 : return "QSOCA_MoreThan10PercentOfRooftopAtLeast5m2";
				case 1 : return "QSOCA_CSCBSC_MoreThan1PercentOfRooftop";
				case 2 : return "QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit";
				case 3 : return "QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277";
				case 4 : return "QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 :
			switch (t) {
				case 0 : return "QSOCASU_AllotmentAndNetworkingFunction";
				case 1 : return "QSOCASU_AccessibilityToPublic";
				case 2 : return "QSOCASU_MeetupAndCommunicationFunction";
				case 3 : return "QSOCASU_ExerciseAndPlayFunction";
				case 4 : return "QSOCASU_WorkAndConcentrationFunction";
				case 5 : return "QSOCASU_RestAndRecuperationFunction";
				case 6 : return "QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation";
				case 7 : return "QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting";
				case 8 : return "QSOCASU_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 :
			switch (t) {
				case 0 : return "QSDCOAC_SolarisationOnDec21AtLeast1Hour";
				case 1 : return "QSDCOAC_SolarisationOnDec21AtLeast3Hours";
				case 2 : return "QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore";
				case 3 : return "QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore";
				case 4 : return "QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures";
				case 5 : return "QSDCOAC_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 :
			switch (t) {
				case 0 : return "QSA2030_ClimateProtectionFactorOfSurfaceStructures";
				case 1 : return "QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas";
			} break;
			// Soc2_1_1::para_t
			case 270 :
			switch (t) {
				case 0 : return "Soc2_1_1Qualitystage";
			} break;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 :
			switch (t) {
				case 0 : return "AQST_ResultsSubmitted";
				case 1 : return "AQST_Residential_StudentHostelBoardingHouses";
				case 2 : return "AQST_Residential_NursingHomesHospicesDisabledElderly";
			} break;
			// Socioculture::para_weights
			case 272 :
			switch (t) {
				case 0 : return "PW_Soc1_1";
				case 1 : return "PW_Soc1_2";
				case 2 : return "PW_Soc1_3";
				case 3 : return "PW_Soc1_4";
				case 4 : return "PW_Soc1_6";
				case 5 : return "PW_Soc2_1";
			} break;
			// Socioculture::para_goals
			case 273 :
			switch (t) {
				case 0 : return "PG_Soc1_1";
				case 1 : return "PG_Soc1_2";
				case 2 : return "PG_Soc1_3";
				case 3 : return "PG_Soc1_4";
				case 4 : return "PG_Soc1_6";
				case 5 : return "PG_Soc2_1";
			} break;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 :
			switch (t) {
				case 0 : return "PABEPFE_PotentialOfSolarEnergy";
				case 1 : return "PABEPFE_PotentialOfGreening";
				case 2 : return "PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle";
				case 3 : return "PABEPFE_UseOfSustainableResourcesForInsulationAndCladding";
				case 4 : return "PABEPFE_PossibilityOfNondestructiveReplacementOfParts";
				case 5 : return "PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope";
			} break;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 :
			switch (t) {
				case 0 : return "TOESEP_NominalRoomTemperature19Degrees";
				case 1 : return "TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18";
				case 2 : return "TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0";
				case 3 : return "TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6";
				case 4 : return "TOESEP_NominalRoomTemperatureBetween12And19Degrees";
				case 5 : return "TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24";
				case 6 : return "TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3";
				case 7 : return "TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0";
				case 8 : return "TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent";
			} break;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 :
			switch (t) {
				case 0 : return "TOESTBS_EvaluationImpossible";
				case 1 : return "TOESTBS_SurchargeLessThan0_05";
				case 2 : return "TOESTBS_SurchargeLessThan0_01";
			} break;
			// Tec1_3_3::para_t
			case 277 :
			switch (t) {
				case 0 : return "Tec1_3_3AirExchangeRateThroughBuildingEnvelope";
				case 1 : return "Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface";
			} break;
			// Tec1_3_3::ABE_Measuring
			case 278 :
			switch (t) {
				case 0 : return "ABEM_BuildingAirVolumeGreaterThan1500sqm";
				case 1 : return "ABEM_BuildingAirVolumeLessThan1500sqm";
				case 2 : return "ABEM_ResultsSubmitted";
			} break;
			// Tec1_3_4::para_t
			case 279 :
			switch (t) {
				case 0 : return "Tec1_3_4UntercuttingOfLegalRequirements";
			} break;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 :
			switch (t) {
				case 0 : return "HISVV_ExaminationOfDifferentVariations";
				case 1 : return "HISVV_ExaminationOfNonCommonRooms";
				case 2 : return "HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning";
				case 3 : return "HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted";
			} break;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 :
			switch (t) {
				case 0 : return "QAMQC_BlowerDoorTest";
				case 1 : return "QAMQC_BuildingThermographyDuringBuildingPhase";
				case 2 : return "QAMQC_OtherRelevantMeasurements";
			} break;
			// Tec1_4_1::PS_Planning
			case 282 :
			switch (t) {
				case 0 : return "PSP_HighCompactness";
				case 1 : return "PSP_BalancedWindowAreaRatioUnderConsiderationOfShading";
				case 2 : return "PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer";
				case 3 : return "PSP_AsManyNaturallyLightedRoomsAsPossible";
				case 4 : return "PSP_UseOfHighMassElementsForHeatStorage";
				case 5 : return "PSP_PassiveCooling";
				case 6 : return "PSP_EffectiveNaturalAeration";
			} break;
			// Tec1_4_1::PS_Implementation
			case 283 :
			switch (t) {
				case 0 : return "PSI_HighCompactness";
				case 1 : return "PSI_BalancedWindowAreaRatioUnderConsiderationOfShading";
				case 2 : return "PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer";
				case 3 : return "PSI_AsManyNaturallyLightedRoomsAsPossible";
				case 4 : return "PSI_UseOfHighMassElementsForHeatStorage";
				case 5 : return "PSI_PassiveCooling";
				case 6 : return "PSI_EffectiveNaturalAeration";
			} break;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 :
			switch (t) {
				case 0 : return "AAOTIREW_AverageTemperatureOf50DegreesOrMore";
				case 1 : return "AAOTIREW_AverageTemperatureBetween35and50Degrees";
				case 2 : return "AAOTIREW_AverageTemperatureOf35DegreesOrLess";
				case 3 : return "AAOTIREW_NoHeatingSystemInBuilding";
				case 4 : return "AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy";
			} break;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 :
			switch (t) {
				case 0 : return "AAOTIREC_AverageTemperatureOf14DegreesOrLess";
				case 1 : return "AAOTIREC_AverageTemperatureBetween14and19Degrees";
				case 2 : return "AAOTIREC_AverageTemperatureOf19DegreesOrMore";
				case 3 : return "AAOTIREC_NoCoolingSystemInBuilding";
				case 4 : return "AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy";
			} break;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 :
			switch (t) {
				case 0 : return "ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting";
				case 1 : return "ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways";
				case 2 : return "ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures";
			} break;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 :
			switch (t) {
				case 0 : return "ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible";
				case 1 : return "ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation";
			} break;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 :
			switch (t) {
				case 0 : return "ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1";
				case 1 : return "ISSU_OpenAndStandardizedProtocolsInExistingNetworks";
			} break;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 :
			switch (t) {
				case 0 : return "ISIFSS_Sunblind";
				case 1 : return "ISIFSS_Lighting";
				case 2 : return "ISIFSS_Heating";
				case 3 : return "ISIFSS_Aeration";
				case 4 : return "ISIFSS_Cooling";
				case 5 : return "ISIFSS_EnergyManagement";
				case 6 : return "ISIFSS_PresenceDetection";
				case 7 : return "ISIFSS_Lifts";
			} break;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 :
			switch (t) {
				case 0 : return "ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure";
				case 1 : return "ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants";
				case 2 : return "ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants";
				case 3 : return "ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers";
			} break;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 :
			switch (t) {
				case 0 : return "ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 :
			switch (t) {
				case 0 : return "ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand";
				case 1 : return "ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 :
			switch (t) {
				case 0 : return "ISIITSMQNES_BuildingProvidesRelevantStorageCapacity";
				case 1 : return "ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement";
			} break;
			// Tec1_4_5::URE_EnergySources
			case 294 :
			switch (t) {
				case 0 : return "UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent";
				case 1 : return "UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent";
			} break;
			// Tec1_4_5::URE_Production
			case 295 :
			switch (t) {
				case 0 : return "UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction";
				case 1 : return "UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction";
				case 2 : return "UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot";
				case 3 : return "UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction";
				case 4 : return "UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction";
				case 5 : return "UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot";
			} break;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 :
			switch (t) {
				case 0 : return "CCPID161_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 :
			switch (t) {
				case 0 : return "SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 :
			switch (t) {
				case 0 : return "SSAPPDCEBSPU_StockPreserved";
				case 1 : return "SSAPPDCEBSPU_StockExpanded";
				case 2 : return "SSAPPDCEBSPU_StockElementsPutToUse";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 :
			switch (t) {
				case 0 : return "SSAPPDDJ_JustificationProvided";
				case 1 : return "SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 :
			switch (t) {
				case 0 : return "SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition";
				case 1 : return "SSAPPDDE_InventoryTakenForMassesAndTransportDistances";
				case 2 : return "SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal";
				case 3 : return "SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 :
			switch (t) {
				case 0 : return "SSAPPDDAC_DGNBDemolitionCertificationFollowed";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 :
			switch (t) {
				case 0 : return "SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject";
			} break;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 :
			switch (t) {
				case 0 : return "CCPID162_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 :
			switch (t) {
				case 0 : return "CCCPGFD_PlanningWithCircularGoal";
				case 1 : return "CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 :
			switch (t) {
				case 0 : return "CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics";
				case 1 : return "CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 :
			switch (t) {
				case 0 : return "CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics";
				case 1 : return "CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices";
				case 2 : return "CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass";
				case 3 : return "CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts";
			} break;
			// Tec1_6_3::para_t
			case 307 :
			switch (t) {
				case 0 : return "CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions";
				case 1 : return "CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering";
			} break;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 :
			switch (t) {
				case 0 : return "CCPID163_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 :
			switch (t) {
				case 0 : return "CCEDDCBPBP_ReducedBuildingPass";
				case 1 : return "CCEDDCBPBP_CompleteBuildingPass";
			} break;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 :
			switch (t) {
				case 0 : return "CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties";
				case 1 : return "CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties";
			} break;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 :
			switch (t) {
				case 0 : return "CCEDUCPCEL_UseOfProductsOfQS4";
				case 1 : return "CCEDUCPCEL_UseOfProductsOfQS3";
				case 2 : return "CCEDUCPCEL_UseOfProductsOfQS2";
				case 3 : return "CCEDUCPCEL_UseOfProductsOfQS1";
				case 4 : return "CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 :
			switch (t) {
				case 0 : return "CCEDCERMACAMMCI_UseOfRecycledMaterials";
				case 1 : return "CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted";
				case 2 : return "CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted";
				case 3 : return "CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations";
			} break;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 :
			switch (t) {
				case 0 : return "CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition";
				case 1 : return "CCEDRRDI_InstructionsIncludeRebuildingAndDemolition";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 :
			switch (t) {
				case 0 : return "CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy";
				case 1 : return "CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy";
				case 2 : return "CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove";
			} break;
			// Tec3_1_1::MI_MobilityConcept
			case 315 :
			switch (t) {
				case 0 : return "MIMC_ConceptIncludesGoalsForSustainableMobility";
				case 1 : return "MIMC_ConceptIncludesFutureTrafficDemands";
			} break;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 :
			switch (t) {
				case 0 : return "IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage";
				case 1 : return "IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers";
			} break;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 :
			switch (t) {
				case 0 : return "IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft";
				case 1 : return "IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection";
				case 2 : return "IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection";
			} break;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 :
			switch (t) {
				case 0 : return "IMIT_ParkingSpacesReducedAccordingToRegulations";
				case 1 : return "IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds";
				case 2 : return "IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing";
				case 3 : return "IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant";
				case 4 : return "IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces";
			} break;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 :
			switch (t) {
				case 0 : return "IA2030MMC_MobilityConceptIncludesMobilityManagementConcept";
			} break;
			// Tec3_1_3::para_t
			case 320 :
			switch (t) {
				case 0 : return "Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots";
				case 1 : return "Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock";
				case 2 : return "Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock";
				case 3 : return "Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock";
				case 4 : return "Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock";
				case 5 : return "Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock";
			} break;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 :
			switch (t) {
				case 0 : return "IAFSBTEB_ResultsSubmitted";
			} break;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 :
			switch (t) {
				case 0 : return "IAFSMIT_ResultsSubmitted";
			} break;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 :
			switch (t) {
				case 0 : return "IAFSILTS_IntegrationIntoBuildingEnergyManagement";
				case 1 : return "IAFSILTS_IntegrationIntoLoadingManagementNetwork";
			} break;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 :
			switch (t) {
				case 0 : return "IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles";
			} break;
			// Tec3_1_4::para_t
			case 325 :
			switch (t) {
				case 0 : return "Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers";
			} break;
			// Tec3_1_4::RS_MobilitySharing
			case 326 :
			switch (t) {
				case 0 : return "RSMS_ResultsSubmitted";
				case 1 : return "RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems";
			} break;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 :
			switch (t) {
				case 0 : return "OCBGO_SufficientAvailabilityOfShowers";
				case 1 : return "OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear";
				case 2 : return "OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes";
				case 3 : return "OCBGO_Residential_ParkingSpacesForBikeTrailers";
			} break;
			// Technology::para_weights
			case 328 :
			switch (t) {
				case 0 : return "PW_Tec1_3";
				case 1 : return "PW_Tec1_4";
				case 2 : return "PW_Tec1_6";
				case 3 : return "PW_Tec3_1";
			} break;
			// Technology::para_goals
			case 329 :
			switch (t) {
				case 0 : return "PG_Tec1_3";
				case 1 : return "PG_Tec1_4";
				case 2 : return "PG_Tec1_6";
				case 3 : return "PG_Tec3_1";
			} break;
			// Utilities::UsageType
			case 330 :
			switch (t) {
				case 0 : return "offices";
				case 1 : return "education";
				case 2 : return "residential";
				case 3 : return "hotel";
				case 4 : return "convenienceStore";
				case 5 : return "shoppingCenter";
				case 6 : return "commercialBuilding";
				case 7 : return "logistics";
				case 8 : return "production";
				case 9 : return "assembly";
				case 10 : return "healthcare";
			} break;
		} // switch
		return INVALID_KEYWORD_INDEX_STRING;
	}

	/*! Returns all keywords including deprecated for a given category (typenum) and type number (t). */
	const char * allKeywords(int typenum, int t) {
		switch (typenum) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 :
			switch (t) {
				case 0 : return "LCCCPIES_Var1SubmissionOfCO2OrClimateCosts";
				case 1 : return "LCCCPIES_Var2SubmissionOfEcologicalSuggestions";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 :
			switch (t) {
				case 0 : return "LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 :
			switch (t) {
				case 0 : return "LCCCPIPE_PartialExaminationsDuringLP2";
				case 1 : return "LCCCPIPE_PartialExaminationsDuringLP3";
				case 2 : return "LCCCPIPE_PartialExaminationsDuringLP4";
				case 3 : return "LCCCPIPE_FundingAdviceSessionByEndOfLP4";
				case 4 : return "LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner";
			} break;
			// Eco1_1_2::para_t
			case 3 :
			switch (t) {
				case 0 : return "CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse";
			} break;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 :
			switch (t) {
				case 0 : return "EECBOBEB_BuildingUpToInnovationClauseStandards";
				case 1 : return "EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter";
			} break;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 :
			switch (t) {
				case 0 : return "EECBOCEBR_CircularEconomySolutionsForReuseSubmitted";
				case 1 : return "EECBOCEBR_LCCModelIncludesEndOfLifeCosts";
				case 2 : return "EECBOCEBR_DocumentationOfRawMaterialValue";
				case 3 : return "currentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse";
			} break;
			// Eco1_1_3::para_t
			case 6 :
			switch (t) {
				case 0 : return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue";
				case 1 : return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue";
				case 2 : return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue";
				case 3 : return "CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts";
				case 4 : return "CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC";
				case 5 : return "ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII";
			} break;
			// Eco1_1_3::BRLCC_Calculation
			case 7 :
			switch (t) {
				case 0 : return "BRLCCC_NetLifeCycleCostsResultsSubmitted";
				case 1 : return "BRLCCC_DisplayCaseFlag";
				case 2 : return "BRLCCC_HealthCareTypeIIFlag";
			} break;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 :
			switch (t) {
				case 0 : return "ASBCSA_GeneralPerceptionOfSite";
				case 1 : return "ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite";
				case 2 : return "ASBCSA_ImmediateNeighbourhood";
			} break;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 :
			switch (t) {
				case 0 : return "ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis";
				case 1 : return "ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects";
			} break;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 :
			switch (t) {
				case 0 : return "ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam";
				case 1 : return "ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes";
				case 2 : return "ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces";
				case 3 : return "ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements";
				case 4 : return "ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding";
				case 5 : return "ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios";
				case 6 : return "ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation";
			} break;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 :
			switch (t) {
				case 0 : return "ATPUSPR_SameUsageType";
				case 1 : return "ATPUSPR_DifferentUsageType";
			} break;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 :
			switch (t) {
				case 0 : return "ATPUSPAIF_CeilingHeight";
				case 1 : return "ATPUSPAIF_BuildingDepth";
				case 2 : return "ATPUSPAIF_FloorAllotment";
				case 3 : return "ATPUSPAIF_GroundPlanFlexibility";
				case 4 : return "ATPUSPAIF_Construction";
				case 5 : return "ATPUSPAIF_BuildingServices";
			} break;
			// Eco2_4_3::para_t
			case 13 :
			switch (t) {
				case 0 : return "CurrentValue_eco2_4_3DegreeOfUseOrTenancy";
			} break;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 :
			switch (t) {
				case 0 : return "DUTTCDUT_ResultsSubmitted";
			} break;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 :
			switch (t) {
				case 0 : return "DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy";
			} break;
			// Eco2_4_4::para_t
			case 16 :
			switch (t) {
				case 0 : return "CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace";
				case 1 : return "ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower";
				case 2 : return "ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper";
			} break;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 :
			switch (t) {
				case 0 : return "SERUSGS_ResultsSubmitted";
				case 1 : return "SERUSGS_LogisticsAndProductionCostOptimisation";
				case 2 : return "SERUSGS_LogisticsAndProductionEnvironmentalOptimisation";
				case 3 : return "SERUSGS_LogisticsAndProductionSocialOptimisation";
			} break;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 :
			switch (t) {
				case 0 : return "SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace";
				case 1 : return "SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace";
			} break;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 :
			switch (t) {
				case 0 : return "SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy";
			} break;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 :
			switch (t) {
				case 0 : return "RAAEF_RiskAnalysisDuringEarlyPlanningPhases";
			} break;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 :
			switch (t) {
				case 0 : return "RABCT_AspirationsForVerification";
				case 1 : return "RABCT_ImplementationOfStandards";
			} break;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 :
			switch (t) {
				case 0 : return "A2030CDI_QualityOfInternetConnection";
			} break;
			// Eco2_4_7::A2030_Expandability
			case 23 :
			switch (t) {
				case 0 : return "A2030E_Concept";
			} break;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 :
			switch (t) {
				case 0 : return "A2030IA_AddressEffect";
			} break;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 :
			switch (t) {
				case 0 : return "BCRMPVPrePH4_ConceptSubmitted";
			} break;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 :
			switch (t) {
				case 0 : return "BCRMPVPostPH4_ConceptSubmitted";
				case 1 : return "BCRMPVPostPH4_ProofOfNoNegativeConcequences";
			} break;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 :
			switch (t) {
				case 0 : return "A2030CBA_Evaluation";
			} break;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 :
			switch (t) {
				case 0 : return "ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented";
				case 1 : return "ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors";
				case 2 : return "ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors";
				case 3 : return "ACCQEM_MeasuresReduceProbableFutureRisksOnSite";
			} break;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 :
			switch (t) {
				case 0 : return "ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions";
				case 1 : return "ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans";
				case 2 : return "ACCQIAM_MeasuresInAccordanceWithNationalStrategy";
				case 3 : return "ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures";
				case 4 : return "ACCQIAM_RegulationOfRemedialMeasures";
			} break;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 :
			switch (t) {
				case 0 : return "ACCGRED_EssentialMeasuresTaken";
				case 1 : return "ACCGRED_GeneralResilienceExists";
			} break;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 :
			switch (t) {
				case 0 : return "ACCA2030HL_ProbableHighHeatLoad";
				case 1 : return "ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 :
			switch (t) {
				case 0 : return "MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity";
				case 1 : return "MAFERSCMAQ_RiskAnalysisConducted";
				case 2 : return "MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 :
			switch (t) {
				case 0 : return "MAFERSCMN_NoiseProtectionConstruction";
				case 1 : return "MAFERSCMN_InclusionOfNoiseProtectionGroundPlans";
				case 2 : return "MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures";
				case 3 : return "MAFERSCMN_OptimisationmeasuresImplemented";
			} break;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 :
			switch (t) {
				case 0 : return "MAFERSRRR_RadonAccessPreventedOrHeavilyHindered";
			} break;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 :
			switch (t) {
				case 0 : return "DCBCPD_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient";
				case 2 : return "DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding";
			} break;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 :
			switch (t) {
				case 0 : return "DCBCSBD_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData";
				case 2 : return "DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation";
				case 3 : return "DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding";
				case 4 : return "DCBCSBD_PartsCatalogueHandedOverToClient";
			} break;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 :
			switch (t) {
				case 0 : return "DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines";
			} break;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 :
			switch (t) {
				case 0 : return "DCBA2030DF_DigitalFootprintHeavilyReduced";
			} break;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 :
			switch (t) {
				case 0 : return "ODBUROMP_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient";
				case 2 : return "ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany";
			} break;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 :
			switch (t) {
				case 0 : return "ODBUOFBM_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany";
				case 2 : return "ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring";
			} break;
			// Eco2_7_3::PPBIM_Preparation
			case 41 :
			switch (t) {
				case 0 : return "PPBIMP_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "PPBIMP_UseOfSharedDataEnvironment";
				case 2 : return "PPBIMP_NecessaryBasicDocuments";
				case 3 : return "PPBIMP_BIMCoordinatorSurveilingModelQuality";
				case 4 : return "PPBIMP_CompetenceCheckAndCoordinationOfBEP";
				case 5 : return "PPBIMP_BIMInformationRequirementsAndGoalsCommunicated";
			} break;
			// Eco2_7_3::PPBIM_Creation
			case 42 :
			switch (t) {
				case 0 : return "PPBIMC_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "PPBIMC_Level0to1_CAD3D";
				case 2 : return "PPBIMC_Level2_BIM4to5D";
				case 3 : return "PPBIMC_Level3_IntegratedBIM6to7D";
			} break;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 :
			switch (t) {
				case 0 : return "PPBIMSO_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "PPBIMSO_VariantsCalculatedAndDocumented";
			} break;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 :
			switch (t) {
				case 0 : return "PPBIMCEBIM2FMOC_SustainableOperatorConcept";
			} break;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 :
			switch (t) {
				case 0 : return "PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted";
			} break;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 :
			switch (t) {
				case 0 : return "DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method";
				case 1 : return "DTOPCHDBM_AsBuiltControlImplementedAndDocumented";
				case 2 : return "DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality";
				case 3 : return "DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable";
			} break;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 :
			switch (t) {
				case 0 : return "DTOPCEDPC_DigitalisationConducted";
			} break;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 :
			switch (t) {
				case 0 : return "DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient";
			} break;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 :
			switch (t) {
				case 0 : return "ACCDT_CircularDigitalTwinImplemented";
			} break;
			// Economy::para_weights
			case 50 :
			switch (t) {
				case 0 : return "PW_Eco1_1";
				case 1 : return "PW_Eco2_4";
				case 2 : return "PW_Eco2_6";
				case 3 : return "PW_Eco2_7";
			} break;
			// Economy::para_goals
			case 51 :
			switch (t) {
				case 0 : return "PG_Eco1_1";
				case 1 : return "PG_Eco2_4";
				case 2 : return "PG_Eco2_6";
				case 3 : return "PG_Eco2_7";
			} break;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 :
			switch (t) {
				case 0 : return "CO2ESOE_HighEnergyStandard";
				case 1 : return "CO2ESOE_CO2NeutralOperation";
				case 2 : return "CO2ESOE_PreparedCO2NeutralOperation";
				case 3 : return "CO2ESOE_SufficiencyStandard";
			} break;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 :
			switch (t) {
				case 0 : return "CO2ESFV_MaterialOptimization";
				case 1 : return "CO2ESFV_CO2ReducedMaterials";
				case 2 : return "CO2ESFV_LowTech";
				case 3 : return "CO2ESFV_CircularDesign";
				case 4 : return "CO2ESFV_Longevity";
			} break;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 :
			switch (t) {
				case 0 : return "CO2PSOE_ElevatedEnergeticStandard";
				case 1 : return "CO2PSOE_NettoGreenhouseGasNeutralOperation";
				case 2 : return "CO2PSOE_SufficiencyStandard";
			} break;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 :
			switch (t) {
				case 0 : return "CO2PSFV_MaterialOptimization";
				case 1 : return "CO2PSFV_CO2ReducedMaterials";
				case 2 : return "CO2PSFV_LowTech";
				case 3 : return "CO2PSFV_CircularDesign";
				case 4 : return "CO2PSFV_Longevity";
			} break;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 :
			switch (t) {
				case 0 : return "CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission";
			} break;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 :
			switch (t) {
				case 0 : return "CO2A2030IPB_IntegrationOfPreexistingBuilding";
			} break;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 :
			switch (t) {
				case 0 : return "CO2A2030MO_ForEmission";
			} break;
			// Env1_1_2::para_t
			case 59 :
			switch (t) {
				case 0 : return "RefEnv1_1_2_2_1				[-]		// ToDo Einheit kg/m2a";
				case 1 : return "CurrentValueEnv1_1_2_2_1	[-]		// ToDo Einheit kg/m2a";
				case 2 : return "RefEnv1_1_2_5_1				[-]		// ToDo Einheit kg/m2a";
				case 3 : return "CurrentValueEnv1_1_2_5_1	[-]		// ToDo Einheit kg/m2a";
			} break;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 :
			switch (t) {
				case 0 : return "LCCO2Disc_GreenHouseGasBalance";
				case 1 : return "LCCO2Disc_NonRenewablePrimaryEnergyBalance";
			} break;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 :
			switch (t) {
				case 0 : return "LCCO2IER_ResultsSubmitted";
			} break;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 :
			switch (t) {
				case 0 : return "LCCO2A2030LCCPA_AgendaSubmitted";
			} break;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 :
			switch (t) {
				case 0 : return "LCCO2A2030CPTS_AgendaSubmitted";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 :
			switch (t) {
				case 0 : return "LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation";
				case 1 : return "LCCO2BFO_AmbitiousClimateProtectionAgenda";
				case 2 : return "LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 :
			switch (t) {
				case 0 : return "LCCO2BFSCO2RCP_ResultsSubmitted";
			} break;
			// Env1_1_3::para_t
			case 66 :
			switch (t) {
				case 0 : return "RefEnv1_1_3_1_1					[-]		// ToDo Einheit kWh/m2a";
				case 1 : return "CurrentValueEnv1_1_3_1_1		[-]		// ToDo Einheit kWh/m2a";
				case 2 : return "RefEnv1_1_3_1_2POCP				[-]		// ToDo Einheit C2H4e/m2a";
				case 3 : return "CurrentValueEnv1_1_3_1_2POCP	[-]		// ToDo Einheit C2H4e/m2a";
				case 4 : return "RefEnv1_1_3_1_2AP				[-]		// ToDo Einheit SO2e/m2a";
				case 5 : return "CurrentValueEnv1_1_3_1_2AP		[-]		// ToDo Einheit SO2e/m2a";
				case 6 : return "RefEnv1_1_3_1_2EP				[-]		// ToDo Einheit PO43/m2a";
				case 7 : return "CurrentValueEnv1_1_3_1_2EP		[-]		// ToDo Einheit PO43/m2a";
				case 8 : return "RefEnv1_1_3_1_2FW				[-]		// ToDo Einheit m3/m2a";
				case 9 : return "CurrentValueEnv1_1_3_1_2FW		[-]		// ToDo Einheit m3/m2a";
			} break;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 :
			switch (t) {
				case 0 : return "CVAEILCPEB_ResultsSubmitted";
			} break;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 :
			switch (t) {
				case 0 : return "CVAEIWRAEI_ResultsSubmitted";
			} break;
			// Env1_2_1::para_t
			case 69 :
			switch (t) {
				case 0 : return "EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows";
				case 1 : return "EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows";
			} break;
			// Env1_2_1::EFM_A
			case 70 :
			switch (t) {
				case 0 : return "EFMA_QS1SimplifiedDocumentation";
				case 1 : return "EFMA_QS2SimplifiedDocumentation";
				case 2 : return "EFMA_QS2MaterialEcologicalComponentCatalogue";
				case 3 : return "EFMA_QS3MaterialEcologicalComponentCatalogue";
				case 4 : return "EFMA_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 :
			switch (t) {
				case 0 : return "EFMBRC_QS1SimplifiedDocumentation";
				case 1 : return "EFMBRC_QS2SimplifiedDocumentation";
				case 2 : return "EFMBRC_QS2MaterialEcologicalComponentCatalogue";
				case 3 : return "EFMBRC_QS3MaterialEcologicalComponentCatalogue";
				case 4 : return "EFMBRC_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 :
			switch (t) {
				case 0 : return "EFMBSC_QS1SimplifiedDocumentation";
				case 1 : return "EFMBSC_QS2SimplifiedDocumentation";
				case 2 : return "EFMBSC_QS2MaterialEcologicalComponentCatalogue";
				case 3 : return "EFMBSC_QS3MaterialEcologicalComponentCatalogue";
				case 4 : return "EFMBSC_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_Agenda2030
			case 73 :
			switch (t) {
				case 0 : return "EFMA2030_1WaivingOfCrossOutCriterionQS3";
				case 1 : return "EFMA2030_2WaivingOfCrossOutCriterionQS4";
				case 2 : return "EFMA2030_MeasurementsTakenForSufficientStructure";
				case 3 : return "EFMA2030_WaivingOfUnsolveableConnections";
				case 4 : return "EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent";
			} break;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 :
			switch (t) {
				case 0 : return "EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent";
			} break;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 :
			switch (t) {
				case 0 : return "RURPESCD_DeclarationOfDiligenceGiven";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 :
			switch (t) {
				case 0 : return "RURPERURP_RegularIntegrationOfMeasures";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 :
			switch (t) {
				case 0 : return "RURPERURED_PartsCatalogue";
			} break;
			// Env1_3_2::para_t
			case 78 :
			switch (t) {
				case 0 : return "Env1_3_2_1NumberOfPartsFromDiffManufacturers";
				case 1 : return "ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup";
				case 2 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4";
				case 3 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2";
				case 4 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4";
				case 5 : return "CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2";
			} break;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 :
			switch (t) {
				case 0 : return "RRMCRRM_ResultSumbitted";
			} break;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 :
			switch (t) {
				case 0 : return "RRMRRWPSR_DetailedMethod";
				case 1 : return "RRMRRWPSR_SimplifiedMethod";
			} break;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 :
			switch (t) {
				case 0 : return "RRMPWMSF_PercentageMinimum50";
			} break;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 :
			switch (t) {
				case 0 : return "RRMPRCEWMPS_Percentage";
			} break;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 :
			switch (t) {
				case 0 : return "DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage";
				case 1 : return "DWDWWVSCWU_FlowClassesOfSanitaryEquipment";
				case 2 : return "DWDWWVSCWU_LocalWaterUsageIndex";
				case 3 : return "DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage";
				case 4 : return "DWDWWVSCWU_EfficentWateringOfOutsideAreas";
				case 5 : return "DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint";
			} break;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 :
			switch (t) {
				case 0 : return "DWDWWVUSC_ConceptUpdatedToPlanningProgress";
				case 1 : return "DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects";
			} break;
			// Env2_2_2::para_t
			case 85 :
			switch (t) {
				case 0 : return "CurrentValue_env2_2WaterUsageIndex";
				case 1 : return "RefValue_env2_2DWDWWVWUI_DynamicThreshold";
			} break;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 :
			switch (t) {
				case 0 : return "DWDWWVWUI_ResultsSubmitted";
			} break;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 :
			switch (t) {
				case 0 : return "DWDWWVIR_NoPlannedIrrigationWithDrinkingWater";
				case 1 : return "DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup";
			} break;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 :
			switch (t) {
				case 0 : return "DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc";
			} break;
			// Env2_2_5::para_t
			case 89 :
			switch (t) {
				case 0 : return "CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation";
				case 1 : return "CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion";
				case 2 : return "CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion";
			} break;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 :
			switch (t) {
				case 0 : return "DWDWWVSC_ResultsSubmitted";
				case 1 : return "DWDWWVSC_InfiltrationPossible";
				case 2 : return "DWDWWVSC_UndercuttingTheDrainagePortion";
			} break;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 :
			switch (t) {
				case 0 : return "DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem";
				case 1 : return "DWDWWVDWS_ObservationOfDrinkingWaterSanitation";
				case 2 : return "DWDWWVDWS_WarmWaterReducedToOperativeMinimum";
				case 3 : return "DWDWWVDWS_ColdWaterLessThan20Degrees";
			} break;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 :
			switch (t) {
				case 0 : return "ADDC_OutlyingDevelopmentArea";
				case 1 : return "ADDC_InternalDevelopmentArea";
				case 2 : return "ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse";
			} break;
			// Env2_3_2::para_t
			case 93 :
			switch (t) {
				case 0 : return "CurrentValue_env2_3_2ADDSAM_DegreeOfSealing";
			} break;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 :
			switch (t) {
				case 0 : return "ADDSAM_ResultsSubmitted";
				case 1 : return "ADDSAM_ImplementationOfAdjustmentMeasures";
			} break;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 :
			switch (t) {
				case 0 : return "ADCEBU_30PercentOfAreaUnsealedPreConstruction";
			} break;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 :
			switch (t) {
				case 0 : return "ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination";
				case 1 : return "ADSQISR_LowContaminationRecyclingAndDisposal";
				case 2 : return "ADSQISR_HighContaminationDisposal";
			} break;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 :
			switch (t) {
				case 0 : return "ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange";
				case 1 : return "ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants";
				case 2 : return "ADSQICEBISSRS_RestorationOfGroundWaterDamages";
			} break;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 :
			switch (t) {
				case 0 : return "BDOSCEBDS_ExtensiveAndLongTermStrategy";
			} break;
			// Env2_4_2::para_t
			case 99 :
			switch (t) {
				case 0 : return "CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea";
				case 1 : return "CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof";
				case 2 : return "CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite";
			} break;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 :
			switch (t) {
				case 0 : return "BDOSBBSA_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 :
			switch (t) {
				case 0 : return "BDOSBGR_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 :
			switch (t) {
				case 0 : return "BDOSBAFA2030VB_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 :
			switch (t) {
				case 0 : return "BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept";
				case 1 : return "BDOSDS_TwoBiotopeStructureTypesAvailable";
			} break;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 :
			switch (t) {
				case 0 : return "BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus";
			} break;
			// Env2_4_3::para_t
			case 105 :
			switch (t) {
				case 0 : return "CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult";
			} break;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 :
			switch (t) {
				case 0 : return "BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies";
				case 1 : return "BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies";
			} break;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 :
			switch (t) {
				case 0 : return "BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept";
				case 1 : return "BDOSVEDLSSS_ResultSubmitted";
			} break;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 :
			switch (t) {
				case 0 : return "BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter";
			} break;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 :
			switch (t) {
				case 0 : return "BDOSRSBI_ConceptDeveloped";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 :
			switch (t) {
				case 0 : return "BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution";
				case 1 : return "BDOSRNIIC_HarmlessLightSourceOrientation";
				case 2 : return "BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature";
				case 3 : return "BDOSRNIIC_NoUnwantedBlindingEffects";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 :
			switch (t) {
				case 0 : return "BDOSRNIAT_EvaluationOfDangersToAnimals";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 :
			switch (t) {
				case 0 : return "BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 :
			switch (t) {
				case 0 : return "BDOSPCMDMCC_ContractSubmitted";
				case 1 : return "BDOSPCMDMCC_EcologicalCarePlanSubmitted";
				case 2 : return "BDOSPCMDMCC_NoUseOfTurfMaterials";
				case 3 : return "BDOSPCMDMCC_NoUseOfHerbicidesOnSite";
				case 4 : return "BDOSPCMDMCC_NoUseOfBiocidesOnSite";
				case 5 : return "BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 :
			switch (t) {
				case 0 : return "BDOSPCMMSC_SimpleMonitoringOfNestingAids";
				case 1 : return "BDOSPCMMSC_ExtensiveMonitoring";
			} break;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 :
			switch (t) {
				case 0 : return "BDOSAC_AlternativeCertificationSubmitted";
			} break;
			// Environment::para_weights
			case 116 :
			switch (t) {
				case 0 : return "PW_Env1_1";
				case 1 : return "PW_Env1_2";
				case 2 : return "PW_Env1_3";
				case 3 : return "PW_Env2_2";
				case 4 : return "PW_Env2_3";
				case 5 : return "PW_Env2_4";
			} break;
			// Environment::para_goals
			case 117 :
			switch (t) {
				case 0 : return "PG_Env1_1";
				case 1 : return "PG_Env1_2";
				case 2 : return "PG_Env1_3";
				case 3 : return "PG_Env2_2";
				case 4 : return "PG_Env2_3";
				case 5 : return "PG_Env2_4";
			} break;
			// KeywordList::MyParameters
			case 118 :
			switch (t) {
				case 0 : return "Temperature";
				case 1 : return "Mass";
			} break;
			// Pro1_1_1::RP_Basis
			case 119 :
			switch (t) {
				case 0 : return "RPB_ImplementationOfDeclarationSustainabilityArchitecture";
				case 1 : return "RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels";
			} break;
			// Pro1_1_1::RP_RP
			case 120 :
			switch (t) {
				case 0 : return "RPRP_PlanFollowsChecklist1OrAnnexe1A";
				case 1 : return "RPRP_PlanFollowsChecklist12OrAnnexe1B";
				case 2 : return "RPRP_PlanFollowsChecklist123OrAnnexe1C";
			} break;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 :
			switch (t) {
				case 0 : return "RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts";
			} break;
			// Pro1_1_2::A2030_Participation
			case 122 :
			switch (t) {
				case 0 : return "A2030P_CounselDuringRequirementAnalysis";
				case 1 : return "A2030P_ParticipationDuringRequirementAnalysis";
				case 2 : return "A2030P_CounselDuringConceptionPhase";
				case 3 : return "A2030P_ParticipationDuringConceptionPhase";
				case 4 : return "A2030P_CounselDuringImplementationPhase";
				case 5 : return "A2030P_ParticipationDuringImplementationPhase";
			} break;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 :
			switch (t) {
				case 0 : return "CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase";
				case 1 : return "CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam";
			} break;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 :
			switch (t) {
				case 0 : return "SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks";
				case 1 : return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks";
				case 2 : return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer";
				case 3 : return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer";
			} break;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 :
			switch (t) {
				case 0 : return "SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer";
			} break;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 :
			switch (t) {
				case 0 : return "CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 :
			switch (t) {
				case 0 : return "CEVCAMSM_ImplementationOfConceptAssignment";
				case 1 : return "CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 :
			switch (t) {
				case 0 : return "CEVCAQE_CompetentDecisionMakingBoard";
				case 1 : return "CEVCAQE_PostProcedureQualityEnsurance";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 :
			switch (t) {
				case 0 : return "CEVMASM_ImplementationOfMultipleAssignments";
				case 1 : return "CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 :
			switch (t) {
				case 0 : return "CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 :
			switch (t) {
				case 0 : return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3";
				case 1 : return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5";
				case 2 : return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 :
			switch (t) {
				case 0 : return "CEVPCSQM_ImplementationOfPlanningCompetition";
				case 1 : return "CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 :
			switch (t) {
				case 0 : return "CEVPCMCM_CooperativeMethod";
				case 1 : return "CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 :
			switch (t) {
				case 0 : return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3";
				case 1 : return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5";
				case 2 : return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 :
			switch (t) {
				case 0 : return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3";
				case 1 : return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5";
				case 2 : return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 :
			switch (t) {
				case 0 : return "RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation";
				case 1 : return "RIDB_ImplementationOfDesignBoardsRecommendations";
			} break;
			// Pro1_6_3::HAA_Recognition
			case 137 :
			switch (t) {
				case 0 : return "HAAR_RecognitionOfGoodConstructionalCulturalQuality";
				case 1 : return "HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond";
			} break;
			// Pro2_1_1::NRCS_Concept
			case 138 :
			switch (t) {
				case 0 : return "NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 :
			switch (t) {
				case 0 : return "NRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 :
			switch (t) {
				case 0 : return "NRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_2::DRCS_Concept
			case 141 :
			switch (t) {
				case 0 : return "DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 :
			switch (t) {
				case 0 : return "DRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 :
			switch (t) {
				case 0 : return "DRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_3::SGPCS_Concept
			case 144 :
			switch (t) {
				case 0 : return "SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 :
			switch (t) {
				case 0 : return "SGPCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 :
			switch (t) {
				case 0 : return "SGPCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_4::WRCS_Concept
			case 147 :
			switch (t) {
				case 0 : return "WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 :
			switch (t) {
				case 0 : return "WRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 :
			switch (t) {
				case 0 : return "WRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 :
			switch (t) {
				case 0 : return "WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies";
			} break;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 :
			switch (t) {
				case 0 : return "CESI_NotificationOfNearbyResidentsOnProjectAndSite";
			} break;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 :
			switch (t) {
				case 0 : return "CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage";
			} break;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 :
			switch (t) {
				case 0 : return "CISI_ParticipantsInProjectProvidedWithAllRelevantInformation";
				case 1 : return "CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite";
				case 2 : return "CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress";
				case 3 : return "CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors";
				case 4 : return "CISI_OnlineAvailabilityOfAllInformation";
			} break;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 :
			switch (t) {
				case 0 : return "RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite";
			} break;
			// Pro2_1_6::RCWU_Concept
			case 155 :
			switch (t) {
				case 0 : return "RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 :
			switch (t) {
				case 0 : return "RCWUIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 :
			switch (t) {
				case 0 : return "RCWUEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 :
			switch (t) {
				case 0 : return "RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite";
			} break;
			// Pro2_1_6::RCEU_Concept
			case 159 :
			switch (t) {
				case 0 : return "RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 :
			switch (t) {
				case 0 : return "RCEUIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 :
			switch (t) {
				case 0 : return "RCEUEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_7::M_Prevention
			case 162 :
			switch (t) {
				case 0 : return "MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite";
			} break;
			// Pro2_3_1::TM_PlanningPhase
			case 163 :
			switch (t) {
				case 0 : return "TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring";
				case 1 : return "TMPP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 :
			switch (t) {
				case 0 : return "TMCP_ContinuationOfAMonitoringConcept";
				case 1 : return "TMCP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_3::TrialOperation
			case 165 :
			switch (t) {
				case 0 : return "TO_TrialOperationConductedPriorToApprovalAndHandover";
				case 1 : return "TO_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 :
			switch (t) {
				case 0 : return "TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation";
				case 1 : return "TMFOP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 :
			switch (t) {
				case 0 : return "TMCM_AssignmentOfACompleteTechnicalMonitoring";
			} break;
			// Pro2_3_6::OperationStartUpManagement
			case 168 :
			switch (t) {
				case 0 : return "OSUM_StartUpManagementInAdditionToTechnicalManagement";
			} break;
			// Pro2_3_7::BuildingPerformance
			case 169 :
			switch (t) {
				case 0 : return "BP_AssignmentOfContinuousImprovementProcessAfterHandover";
			} break;
			// Pro2_5_1::FM_Check
			case 170 :
			switch (t) {
				case 0 : return "FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage";
			} break;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 :
			switch (t) {
				case 0 : return "MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors";
				case 1 : return "MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400";
				case 2 : return "MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation";
			} break;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 :
			switch (t) {
				case 0 : return "FMG_CreationAndHandoverToFacilityManager";
			} break;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 :
			switch (t) {
				case 0 : return "CWU_CreationAndHandoverTechnicalOperationHandbook";
				case 1 : return "CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase";
			} break;
			// Pro2_5_5::SIS_Implementation
			case 174 :
			switch (t) {
				case 0 : return "SISI_CreationOfConceptIncludingImplementationPlan";
				case 1 : return "SISI_InstallationOfSustainabilityInformationSystem";
			} break;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 :
			switch (t) {
				case 0 : return "SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept";
				case 1 : return "SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses";
			} break;
			// Pro2_5_6::OCP_Extended
			case 176 :
			switch (t) {
				case 0 : return "OCPE_CreationOfExtendedOperationCostPrognosis";
			} break;
			// Process::para_weights
			case 177 :
			switch (t) {
				case 0 : return "PW_Pro1_1";
				case 1 : return "PW_Pro1_4";
				case 2 : return "PW_Pro1_6";
				case 3 : return "PW_Pro2_1";
				case 4 : return "PW_Pro2_3";
				case 5 : return "PW_Pro2_5";
			} break;
			// Process::para_goals
			case 178 :
			switch (t) {
				case 0 : return "PG_Pro1_1";
				case 1 : return "PG_Pro1_4";
				case 2 : return "PG_Pro1_6";
				case 3 : return "PG_Pro2_1";
				case 4 : return "PG_Pro2_3";
				case 5 : return "PG_Pro2_5";
			} break;
			// Site::para_weights
			case 179 :
			switch (t) {
				case 0 : return "PW_Site1_1";
				case 1 : return "PW_Site1_3";
				case 2 : return "PW_Site1_4";
			} break;
			// Site::para_goals
			case 180 :
			switch (t) {
				case 0 : return "PG_Site1_1";
				case 1 : return "PG_Site1_3";
				case 2 : return "PG_Site1_4";
			} break;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 :
			switch (t) {
				case 0 : return "CRCA_ConductionOfAnalysis";
				case 1 : return "CRCA_ConductionOfQualifiedAnalysisByExperts";
			} break;
			// Site1_1_1::CR_Screening
			case 182 :
			switch (t) {
				case 0 : return "CRS_AppendixA3TableA";
				case 1 : return "CRS_AppendixA3TableB";
				case 2 : return "CRS_AdditionallyAppendixA3TableC";
			} break;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 :
			switch (t) {
				case 0 : return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years";
				case 1 : return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years";
				case 2 : return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy";
			} break;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 :
			switch (t) {
				case 0 : return "CRAT_EvaluationOfEnvironmentAndClimateHazardProbability";
				case 1 : return "CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue";
			} break;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 :
			switch (t) {
				case 0 : return "CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers";
			} break;
			// Site1_1_1::CR_DataBasis
			case 186 :
			switch (t) {
				case 0 : return "CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85";
				case 1 : return "CRDB_AdditionallyScenarioRCP6_0";
				case 2 : return "CRDB_AdditionallyScenarioRCP4_5";
				case 3 : return "CRDB_AdditionallyScenarioRCP2_6";
			} break;
			// Site1_1_1::CR_ResultApplication
			case 187 :
			switch (t) {
				case 0 : return "CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction";
			} break;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 :
			switch (t) {
				case 0 : return "ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue";
			} break;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 :
			switch (t) {
				case 0 : return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB";
				case 1 : return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB";
				case 2 : return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB";
			} break;
			// Site1_1_3::EEI_AirQuality
			case 190 :
			switch (t) {
				case 0 : return "EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually";
				case 1 : return "EEIAQ_PM10NeverExceedsLimit";
				case 2 : return "EEIAQ_PM2_5NeverExceedsLimit";
				case 3 : return "EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually";
				case 4 : return "EEIAQ_NO2NeverExceedsExceedsLimit";
			} break;
			// Site1_1_3::EEI_Radon
			case 191 :
			switch (t) {
				case 0 : return "EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation";
				case 1 : return "EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation";
				case 2 : return "EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured";
				case 3 : return "EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings";
			} break;
			// Site1_3_1::MIT_Surroundings
			case 192 :
			switch (t) {
				case 0 : return "MITS_ConnectionToBundesstrasseA_Road";
				case 1 : return "MITS_ConnectionToFreeway";
				case 2 : return "MITS_ConnectionToMainStreet";
			} break;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 :
			switch (t) {
				case 0 : return "MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter";
			} break;
			// Site1_3_2::PT_Stations
			case 194 :
			switch (t) {
				case 0 : return "PTS_DistancedWithin350Meters";
			} break;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 :
			switch (t) {
				case 0 : return "PTDTSHD_NoMoreThan20Minutes";
				case 1 : return "PTDTSHD_NoMoreThan15Minutes";
				case 2 : return "PTDTSHD_NoMoreThan10Minutes";
			} break;
			// Site1_3_2::PT_Intervals
			case 196 :
			switch (t) {
				case 0 : return "PTI_NoMoreThan15Minutes";
				case 1 : return "PTI_NoMoreThan10Minutes";
				case 2 : return "PTI_NoMoreThan5Minutes";
			} break;
			// Site1_3_2::PT_RelationToBuilding
			case 197 :
			switch (t) {
				case 0 : return "PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay";
				case 1 : return "PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances";
				case 2 : return "PTRB_BuildingFeaturesSignageToStations";
			} break;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 :
			switch (t) {
				case 0 : return "BTCT500M_PartialMixWithMotorTraffic";
				case 1 : return "BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks";
			} break;
			// Site1_3_3::BT_Connection
			case 199 :
			switch (t) {
				case 0 : return "BTC_ContinuousRegionalConnection";
				case 1 : return "BTC_ContinuousInterregionalConnectionMoreThan10KM";
			} break;
			// Site1_3_3::BT_RelationToBuilding
			case 200 :
			switch (t) {
				case 0 : return "BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks";
			} break;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 :
			switch (t) {
				case 0 : return "FTWN350M_50PercentOrMoreCoverage";
				case 1 : return "FTWN350M_80PercentOrMoreCoverage";
				case 2 : return "FTWN350M_100PercentCoverage";
			} break;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 :
			switch (t) {
				case 0 : return "FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach";
				case 1 : return "FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach";
			} break;
			// Site1_3_4::FT_SignageSystems
			case 203 :
			switch (t) {
				case 0 : return "FTSS_SignageCoversSurroundingArea";
				case 1 : return "FTSS_SignageAndOrientationPlansCoverSurroundingArea";
			} break;
			// Site1_3_5::AS_Within350Meters
			case 204 :
			switch (t) {
				case 0 : return "ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots";
				case 1 : return "ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots";
			} break;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 :
			switch (t) {
				case 0 : return "ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs";
			} break;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 :
			switch (t) {
				case 0 : return "A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters";
			} break;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 :
			switch (t) {
				case 0 : return "SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters";
				case 1 : return "SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters";
				case 2 : return "SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 3 : return "SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 4 : return "SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 5 : return "SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 6 : return "SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 7 : return "SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 8 : return "SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 9 : return "SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers";
				case 10 : return "SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters";
				case 11 : return "SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
			} break;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 :
			switch (t) {
				case 0 : return "SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily";
				case 1 : return "SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours";
				case 2 : return "SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes";
			} break;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 :
			switch (t) {
				case 0 : return "POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 1 : return "POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 2 : return "POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 3 : return "POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 4 : return "POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 5 : return "POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 6 : return "POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
			} break;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 :
			switch (t) {
				case 0 : return "BAIUDIHD_Daycare";
				case 1 : return "BAIUDIHD_SecondaryOrVocationalSchool";
				case 2 : return "BAIUDIHD_CinemaTheatreOrGallery";
				case 3 : return "BAIUDIHD_Bookstore";
				case 4 : return "BAIUDIHD_QuarterCenter";
				case 5 : return "BAIUDIHD_ParishHall";
				case 6 : return "BAIUDIHD_YouthCenter";
				case 7 : return "BAIUDIHD_ElderlyCenter";
				case 8 : return "BAIUDIHD_FitnessCenter";
				case 9 : return "BAIUDIHD_FitnessProgramOpenToExternalUsers";
				case 10 : return "BAIUDIHD_Playground";
				case 11 : return "BAIUDIHD_GymSportsFieldOrSwimmingPool";
				case 12 : return "BAIUDIHD_LocalAmeneties1_ShoppingCenter";
				case 13 : return "BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc";
				case 14 : return "BAIUDIHD_LocalAmeneties3_FarmersMarket";
				case 15 : return "BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc";
				case 16 : return "BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter";
				case 17 : return "BAIUDIHD_Healthcare1_GeneralPractitioner";
				case 18 : return "BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc";
			} break;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 :
			switch (t) {
				case 0 : return "BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals";
				case 1 : return "BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers";
			} break;
			// Soc1_1_1::para_t
			case 212 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad";
			} break;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 :
			switch (t) {
				case 0 : return "OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3";
				case 1 : return "OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2";
				case 2 : return "OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification";
				case 3 : return "OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3";
				case 4 : return "OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2";
				case 5 : return "OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees";
				case 6 : return "OTRTOT_LogisticsAndProductionLimitationTo30Degrees";
			} break;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 :
			switch (t) {
				case 0 : return "RHHP_RelativeHumidityHigherThan30Percent";
				case 1 : return "RHHP_HotelRelativeHumidityLowerThan70Percent";
				case 2 : return "RHHP_ConditionMetFor95PercentOfTime";
			} break;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 :
			switch (t) {
				case 0 : return "RHCP_MaxHumidity12GramPerKilogram";
			} break;
			// Soc1_1_3::D_CoolingPeriod
			case 216 :
			switch (t) {
				case 0 : return "DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB";
				case 1 : return "DCP_ShoppingCenterPreventionOfDraught";
			} break;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 :
			switch (t) {
				case 0 : return "RTAFTCP_CeilingMin16Degrees";
				case 1 : return "RTAFTCP_CeilingMax35Degrees";
				case 2 : return "RTAFTCP_GlassSurfacesMin18Degrees";
				case 3 : return "RTAFTCP_GlassSurfacesMax35Degrees";
				case 4 : return "RTAFTCP_FloorMin19Degrees";
				case 5 : return "RTAFTCP_FloorMax29Degrees";
				case 6 : return "RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA";
			} break;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 :
			switch (t) {
				case 0 : return "A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture";
				case 1 : return "A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess";
			} break;
			// Soc1_1_6::UI_UserInfluence
			case 219 :
			switch (t) {
				case 0 : return "UI_PossibilityOfReuse";
				case 1 : return "UI_RoomAirCycleIndividuallyManipulable";
				case 2 : return "UI_RoomTemperatureIndividuallyManipulable";
				case 3 : return "UI_SurveyOnUserSatisfactionAndEnergyEfficiency";
			} break;
			// Soc1_1_Alt::AC_Innovation
			case 220 :
			switch (t) {
				case 0 : return "AC_AlternativeCertificationForIndicators1to4";
			} break;
			// Soc1_2_1::para_t
			case 221 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_2_TVOC";
				case 1 : return "CurrentValue_soc1_2_Formaldehyde";
				case 2 : return "CurrentValue_soc1_2_TVOCRenterPromise";
				case 3 : return "CurrentValue_soc1_2_FormaldehydeRenterPromise";
			} break;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 :
			switch (t) {
				case 0 : return "IHTVOCM_TVOCResultsSubmitted";
				case 1 : return "IHTVOCM_FormaldehydeResultsSubmitted";
				case 2 : return "IHTVOCM_AlternativeCertification";
				case 3 : return "IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent";
				case 4 : return "IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors";
				case 5 : return "IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces";
			} break;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 :
			switch (t) {
				case 0 : return "IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed";
				case 1 : return "IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces";
				case 2 : return "IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces";
			} break;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 :
			switch (t) {
				case 0 : return "IHTVOCA2030IATMRHC_NonSmokerProtection";
				case 1 : return "IHTVOCA2030IATMRHC_RespirableDustPrevention";
			} break;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 :
			switch (t) {
				case 0 : return "IHTVOCWWB_WoodworkApplicable";
				case 1 : return "IHTVOCWWB_LimoneneBelowNOW";
				case 2 : return "IHTVOCWWB_AlphaPineneBelowNOW";
			} break;
			// Soc1_2_2::para_t
			case 226 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration";
				case 1 : return "CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 :
			switch (t) {
				case 0 : return "IHACFOEHAH_RatioSubmitted";
				case 1 : return "IHACFOEHAH_ZonalStreamingSimulation";
				case 2 : return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3";
				case 3 : return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2";
				case 4 : return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1";
				case 5 : return "IHACFOEHAH_ManualNoCertification";
				case 6 : return "IHACFOEHAH_ManualObservationOfASR3_6";
				case 7 : return "IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring";
				case 8 : return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4";
				case 9 : return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3";
				case 10 : return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 :
			switch (t) {
				case 0 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops";
				case 1 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops";
				case 2 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops";
				case 3 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls";
				case 4 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls";
				case 5 : return "IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 :
			switch (t) {
				case 0 : return "IHACFR_AerationMeasuresAccordingToLevelsFL";
				case 1 : return "IHACFR_AerationMeasuresAccordingToLevelsRL";
				case 2 : return "IHACFR_AerationMeasuresAccordingToLevelsNL";
			} break;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 :
			switch (t) {
				case 0 : return "IHACFLP_NoCertification";
				case 1 : return "IHACFLP_ObservationOfASR3_6";
				case 2 : return "IHACFLP_NeedbasedAeration";
				case 3 : return "IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent";
			} break;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 :
			switch (t) {
				case 0 : return "ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet";
			} break;
			// Soc1_3_1::ORSR_Office
			case 232 :
			switch (t) {
				case 0 : return "ORSRO_ObservationOfVDI_2569_ClassAorBRequirements";
			} break;
			// Soc1_3_1::ORSR_Residential
			case 233 :
			switch (t) {
				case 0 : return "ORSRR_DIN_4109_5_RequirementsMet";
				case 1 : return "ORSRR_SoundproofingPassClassCOrBetter";
			} break;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 :
			switch (t) {
				case 0 : return "BAMOEHAHcR_ConfirmationThroughMeasuring";
			} break;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 :
			switch (t) {
				case 0 : return "PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept";
			} break;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 :
			switch (t) {
				case 0 : return "RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB";
				case 1 : return "RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse";
				case 2 : return "RAHHcAEO_ObservationOfVDI_2569ClassA";
				case 3 : return "RAHHcAEO_ObservationOfVDI_2569ClassB";
				case 4 : return "RAHHcAEO_MeasuresTakenAndVerified";
			} break;
			// Soc1_3_3::RA_Residential
			case 237 :
			switch (t) {
				case 0 : return "RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways";
				case 1 : return "RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms";
			} break;
			// Soc1_4_1::para_t
			case 238 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_1ET";
				case 1 : return "CurrentValue_soc1_4_1D";
				case 2 : return "CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea";
			} break;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 :
			switch (t) {
				case 0 : return "DSOEARHHcP_ResultsSubmitted";
				case 1 : return "DSOEARHHcP_HotelAlternativeCertification";
			} break;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 :
			switch (t) {
				case 0 : return "DSOCSSCCB_ResultsSubmitted";
				case 1 : return "DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight";
			} break;
			// Soc1_4_2::para_t
			case 241 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_2UsageLighting";
				case 1 : return "CurrentValue_soc1_4_2TranslucentCeilingLightPortion";
			} break;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 :
			switch (t) {
				case 0 : return "ARULOEALHc_UsageLightingResultsSubmitted";
				case 1 : return "ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted";
				case 2 : return "ARULOEALHc_AssemblyAreaType1";
				case 3 : return "ARULOEALHc_AssemblyAreaType2";
			} break;
			// Soc1_4_3::para_t
			case 243 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_3_1aPercentageOfOpenFacade";
				case 1 : return "CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside";
			} break;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 :
			switch (t) {
				case 0 : return "LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms";
				case 1 : return "LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted";
				case 2 : return "LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS";
				case 3 : return "LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted";
				case 4 : return "LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS";
			} break;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 :
			switch (t) {
				case 0 : return "LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility";
				case 1 : return "LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility";
				case 2 : return "LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility";
				case 3 : return "LOSOOEHLARHc_RHHc_AlternativeRequirementsMet";
				case 4 : return "LOSOOEHLARHc_AssemblyType1";
				case 5 : return "LOSOOEHLARHc_AssemblyType2";
				case 6 : return "LOSOOEHLARHc_AnyDaylightInCommonAreas";
				case 7 : return "LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility";
				case 8 : return "LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility";
			} break;
			// Soc1_4_4::para_t
			case 246 :
			switch (t) {
				case 0 : return "CurrentValue_soc1_4_4_1DaylightGlareProbability";
			} break;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 :
			switch (t) {
				case 0 : return "DGSOEA12Hc_DGPResultsSubmitted";
				case 1 : return "DGSOEA12Hc_AssemblyType1";
				case 2 : return "DGSOEA12Hc_AssemblyType2";
				case 3 : return "DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields";
				case 4 : return "DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights";
			} break;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 :
			switch (t) {
				case 0 : return "DGSCS_ObservationOfASRA3_4Chapter4_2";
			} break;
			// Soc1_4_4::DGS_Logistics
			case 249 :
			switch (t) {
				case 0 : return "DGSL_UncertifiedGlareShieldSystem";
				case 1 : return "DGSL_Class2GlareShieldSystem";
				case 2 : return "DGSL_Class3OrHigherGlareShieldSystem";
			} break;
			// Soc1_4_4::DGS_Production
			case 250 :
			switch (t) {
				case 0 : return "DGSP_CombinationOfLightDivertingSystemsAndGlareShields";
				case 1 : return "DGSP_UseOfHighNorthLightDiffusionCeilingLights";
			} break;
			// Soc1_4_5::AL_LightingConcept
			case 251 :
			switch (t) {
				case 0 : return "ALLC_CreationOfLightingConcept";
			} break;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 :
			switch (t) {
				case 0 : return "ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet";
				case 1 : return "ALIPCOR_AtLeastTwoOptimisationMeasuresTaken";
				case 2 : return "ALIPCOR_AdditionalOptimisationMeasuresTaken";
			} break;
			// Soc1_4_6::SED_Residential
			case 253 :
			switch (t) {
				case 0 : return "SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit";
				case 1 : return "SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit";
				case 2 : return "SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit";
			} break;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 :
			switch (t) {
				case 0 : return "SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms";
				case 1 : return "SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms";
				case 2 : return "SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent";
				case 3 : return "SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent";
			} break;
			// Soc1_6_1::para_t
			case 255 :
			switch (t) {
				case 0 : return "AlternativeInnovativeCommunicationConstellations";
			} break;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 :
			switch (t) {
				case 0 : return "CSOCZMU_DifferentCommunicationZones";
				case 1 : return "CSOCZMU_CommunicationSupportingRoomDesign";
				case 2 : return "CSOCZMU_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_2::para_t
			case 257 :
			switch (t) {
				case 0 : return "Soc1_6_2_1AlternativeInnovativeSolutions";
				case 1 : return "Soc1_6_2_2AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 :
			switch (t) {
				case 0 : return "AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms";
				case 1 : return "AOUAOS_CSCBSC_LockersChangingRooms";
				case 2 : return "AOUAOS_Residential_CommonRoomsAvailableToEveryone";
				case 3 : return "AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits";
				case 4 : return "AOUAOS_Hc_AdditionalOffersAvailableToEveryone";
				case 5 : return "AOUAOS_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 :
			switch (t) {
				case 0 : return "AOUOI_Signage";
				case 1 : return "AOUOI_InformationDesk";
				case 2 : return "AOUOI_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_3::para_t
			case 260 :
			switch (t) {
				case 0 : return "Soc1_6_3_1AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 :
			switch (t) {
				case 0 : return "FCEFOSO_Daycare";
				case 1 : return "FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms";
				case 2 : return "FCEFOSO_Playground";
				case 3 : return "FCEFOSO_ElderlyCommonRoomsPlayrooms";
				case 4 : return "FCEFOSO_FamilyFriendlyParking";
				case 5 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange";
				case 6 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib";
				case 7 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette";
				case 8 : return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind";
				case 9 : return "FCEFOSO_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_4::para_t
			case 262 :
			switch (t) {
				case 0 : return "Soc1_6_4_1AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 :
			switch (t) {
				case 0 : return "QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication";
				case 1 : return "QSIAA_DaylightAvailabilityInAllotmentAreas";
				case 2 : return "QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria";
				case 3 : return "QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse";
				case 4 : return "QSIAA_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::para_t
			case 264 :
			switch (t) {
				case 0 : return "Soc1_6_5_3AlternativeInnovativeSolutions";
				case 1 : return "Soc1_6_5_4AlternativeInnovativePoints";
			} break;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 :
			switch (t) {
				case 0 : return "QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions";
				case 1 : return "QSDCOA_DesignConsidersMaterialQuality";
				case 2 : return "QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting";
				case 3 : return "QSDCOA_DesignConsidersIntuitiveOrientation";
				case 4 : return "QSDCOA_DesignAvoidsPlacesOfAnxiety";
				case 5 : return "QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities";
				case 6 : return "QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents";
				case 7 : return "QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 :
			switch (t) {
				case 0 : return "QSOCA_MoreThan10PercentOfRooftopAtLeast5m2";
				case 1 : return "QSOCA_CSCBSC_MoreThan1PercentOfRooftop";
				case 2 : return "QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit";
				case 3 : return "QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277";
				case 4 : return "QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 :
			switch (t) {
				case 0 : return "QSOCASU_AllotmentAndNetworkingFunction";
				case 1 : return "QSOCASU_AccessibilityToPublic";
				case 2 : return "QSOCASU_MeetupAndCommunicationFunction";
				case 3 : return "QSOCASU_ExerciseAndPlayFunction";
				case 4 : return "QSOCASU_WorkAndConcentrationFunction";
				case 5 : return "QSOCASU_RestAndRecuperationFunction";
				case 6 : return "QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation";
				case 7 : return "QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting";
				case 8 : return "QSOCASU_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 :
			switch (t) {
				case 0 : return "QSDCOAC_SolarisationOnDec21AtLeast1Hour";
				case 1 : return "QSDCOAC_SolarisationOnDec21AtLeast3Hours";
				case 2 : return "QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore";
				case 3 : return "QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore";
				case 4 : return "QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures";
				case 5 : return "QSDCOAC_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 :
			switch (t) {
				case 0 : return "QSA2030_ClimateProtectionFactorOfSurfaceStructures";
				case 1 : return "QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas";
			} break;
			// Soc2_1_1::para_t
			case 270 :
			switch (t) {
				case 0 : return "Soc2_1_1Qualitystage";
			} break;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 :
			switch (t) {
				case 0 : return "AQST_ResultsSubmitted";
				case 1 : return "AQST_Residential_StudentHostelBoardingHouses";
				case 2 : return "AQST_Residential_NursingHomesHospicesDisabledElderly";
			} break;
			// Socioculture::para_weights
			case 272 :
			switch (t) {
				case 0 : return "PW_Soc1_1";
				case 1 : return "PW_Soc1_2";
				case 2 : return "PW_Soc1_3";
				case 3 : return "PW_Soc1_4";
				case 4 : return "PW_Soc1_6";
				case 5 : return "PW_Soc2_1";
			} break;
			// Socioculture::para_goals
			case 273 :
			switch (t) {
				case 0 : return "PG_Soc1_1";
				case 1 : return "PG_Soc1_2";
				case 2 : return "PG_Soc1_3";
				case 3 : return "PG_Soc1_4";
				case 4 : return "PG_Soc1_6";
				case 5 : return "PG_Soc2_1";
			} break;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 :
			switch (t) {
				case 0 : return "PABEPFE_PotentialOfSolarEnergy";
				case 1 : return "PABEPFE_PotentialOfGreening";
				case 2 : return "PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle";
				case 3 : return "PABEPFE_UseOfSustainableResourcesForInsulationAndCladding";
				case 4 : return "PABEPFE_PossibilityOfNondestructiveReplacementOfParts";
				case 5 : return "PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope";
			} break;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 :
			switch (t) {
				case 0 : return "TOESEP_NominalRoomTemperature19Degrees";
				case 1 : return "TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18";
				case 2 : return "TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0";
				case 3 : return "TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6";
				case 4 : return "TOESEP_NominalRoomTemperatureBetween12And19Degrees";
				case 5 : return "TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24";
				case 6 : return "TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3";
				case 7 : return "TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0";
				case 8 : return "TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent";
			} break;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 :
			switch (t) {
				case 0 : return "TOESTBS_EvaluationImpossible";
				case 1 : return "TOESTBS_SurchargeLessThan0_05";
				case 2 : return "TOESTBS_SurchargeLessThan0_01";
			} break;
			// Tec1_3_3::para_t
			case 277 :
			switch (t) {
				case 0 : return "Tec1_3_3AirExchangeRateThroughBuildingEnvelope";
				case 1 : return "Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface		[-]		// ToDo Einheit";
			} break;
			// Tec1_3_3::ABE_Measuring
			case 278 :
			switch (t) {
				case 0 : return "ABEM_BuildingAirVolumeGreaterThan1500sqm";
				case 1 : return "ABEM_BuildingAirVolumeLessThan1500sqm";
				case 2 : return "ABEM_ResultsSubmitted";
			} break;
			// Tec1_3_4::para_t
			case 279 :
			switch (t) {
				case 0 : return "Tec1_3_4UntercuttingOfLegalRequirements";
			} break;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 :
			switch (t) {
				case 0 : return "HISVV_ExaminationOfDifferentVariations";
				case 1 : return "HISVV_ExaminationOfNonCommonRooms";
				case 2 : return "HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning";
				case 3 : return "HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted";
			} break;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 :
			switch (t) {
				case 0 : return "QAMQC_BlowerDoorTest";
				case 1 : return "QAMQC_BuildingThermographyDuringBuildingPhase";
				case 2 : return "QAMQC_OtherRelevantMeasurements";
			} break;
			// Tec1_4_1::PS_Planning
			case 282 :
			switch (t) {
				case 0 : return "PSP_HighCompactness";
				case 1 : return "PSP_BalancedWindowAreaRatioUnderConsiderationOfShading";
				case 2 : return "PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer";
				case 3 : return "PSP_AsManyNaturallyLightedRoomsAsPossible";
				case 4 : return "PSP_UseOfHighMassElementsForHeatStorage";
				case 5 : return "PSP_PassiveCooling";
				case 6 : return "PSP_EffectiveNaturalAeration";
			} break;
			// Tec1_4_1::PS_Implementation
			case 283 :
			switch (t) {
				case 0 : return "PSI_HighCompactness";
				case 1 : return "PSI_BalancedWindowAreaRatioUnderConsiderationOfShading";
				case 2 : return "PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer";
				case 3 : return "PSI_AsManyNaturallyLightedRoomsAsPossible";
				case 4 : return "PSI_UseOfHighMassElementsForHeatStorage";
				case 5 : return "PSI_PassiveCooling";
				case 6 : return "PSI_EffectiveNaturalAeration";
			} break;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 :
			switch (t) {
				case 0 : return "AAOTIREW_AverageTemperatureOf50DegreesOrMore";
				case 1 : return "AAOTIREW_AverageTemperatureBetween35and50Degrees";
				case 2 : return "AAOTIREW_AverageTemperatureOf35DegreesOrLess";
				case 3 : return "AAOTIREW_NoHeatingSystemInBuilding";
				case 4 : return "AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy";
			} break;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 :
			switch (t) {
				case 0 : return "AAOTIREC_AverageTemperatureOf14DegreesOrLess";
				case 1 : return "AAOTIREC_AverageTemperatureBetween14and19Degrees";
				case 2 : return "AAOTIREC_AverageTemperatureOf19DegreesOrMore";
				case 3 : return "AAOTIREC_NoCoolingSystemInBuilding";
				case 4 : return "AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy";
			} break;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 :
			switch (t) {
				case 0 : return "ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting";
				case 1 : return "ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways";
				case 2 : return "ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures";
			} break;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 :
			switch (t) {
				case 0 : return "ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible";
				case 1 : return "ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation";
			} break;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 :
			switch (t) {
				case 0 : return "ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1";
				case 1 : return "ISSU_OpenAndStandardizedProtocolsInExistingNetworks";
			} break;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 :
			switch (t) {
				case 0 : return "ISIFSS_Sunblind";
				case 1 : return "ISIFSS_Lighting";
				case 2 : return "ISIFSS_Heating";
				case 3 : return "ISIFSS_Aeration";
				case 4 : return "ISIFSS_Cooling";
				case 5 : return "ISIFSS_EnergyManagement";
				case 6 : return "ISIFSS_PresenceDetection";
				case 7 : return "ISIFSS_Lifts";
			} break;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 :
			switch (t) {
				case 0 : return "ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure";
				case 1 : return "ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants";
				case 2 : return "ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants";
				case 3 : return "ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers";
			} break;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 :
			switch (t) {
				case 0 : return "ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 :
			switch (t) {
				case 0 : return "ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand";
				case 1 : return "ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 :
			switch (t) {
				case 0 : return "ISIITSMQNES_BuildingProvidesRelevantStorageCapacity";
				case 1 : return "ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement";
			} break;
			// Tec1_4_5::URE_EnergySources
			case 294 :
			switch (t) {
				case 0 : return "UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent";
				case 1 : return "UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent";
			} break;
			// Tec1_4_5::URE_Production
			case 295 :
			switch (t) {
				case 0 : return "UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction";
				case 1 : return "UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction";
				case 2 : return "UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot";
				case 3 : return "UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction";
				case 4 : return "UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction";
				case 5 : return "UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot";
			} break;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 :
			switch (t) {
				case 0 : return "CCPID161_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 :
			switch (t) {
				case 0 : return "SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 :
			switch (t) {
				case 0 : return "SSAPPDCEBSPU_StockPreserved";
				case 1 : return "SSAPPDCEBSPU_StockExpanded";
				case 2 : return "SSAPPDCEBSPU_StockElementsPutToUse";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 :
			switch (t) {
				case 0 : return "SSAPPDDJ_JustificationProvided";
				case 1 : return "SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 :
			switch (t) {
				case 0 : return "SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition";
				case 1 : return "SSAPPDDE_InventoryTakenForMassesAndTransportDistances";
				case 2 : return "SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal";
				case 3 : return "SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 :
			switch (t) {
				case 0 : return "SSAPPDDAC_DGNBDemolitionCertificationFollowed";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 :
			switch (t) {
				case 0 : return "SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject";
			} break;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 :
			switch (t) {
				case 0 : return "CCPID162_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 :
			switch (t) {
				case 0 : return "CCCPGFD_PlanningWithCircularGoal";
				case 1 : return "CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 :
			switch (t) {
				case 0 : return "CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics";
				case 1 : return "CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 :
			switch (t) {
				case 0 : return "CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics";
				case 1 : return "CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices";
				case 2 : return "CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass";
				case 3 : return "CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts";
			} break;
			// Tec1_6_3::para_t
			case 307 :
			switch (t) {
				case 0 : return "CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions";
				case 1 : return "CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering";
			} break;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 :
			switch (t) {
				case 0 : return "CCPID163_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 :
			switch (t) {
				case 0 : return "CCEDDCBPBP_ReducedBuildingPass";
				case 1 : return "CCEDDCBPBP_CompleteBuildingPass";
			} break;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 :
			switch (t) {
				case 0 : return "CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties";
				case 1 : return "CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties";
			} break;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 :
			switch (t) {
				case 0 : return "CCEDUCPCEL_UseOfProductsOfQS4";
				case 1 : return "CCEDUCPCEL_UseOfProductsOfQS3";
				case 2 : return "CCEDUCPCEL_UseOfProductsOfQS2";
				case 3 : return "CCEDUCPCEL_UseOfProductsOfQS1";
				case 4 : return "CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 :
			switch (t) {
				case 0 : return "CCEDCERMACAMMCI_UseOfRecycledMaterials";
				case 1 : return "CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted";
				case 2 : return "CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted";
				case 3 : return "CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations";
			} break;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 :
			switch (t) {
				case 0 : return "CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition";
				case 1 : return "CCEDRRDI_InstructionsIncludeRebuildingAndDemolition";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 :
			switch (t) {
				case 0 : return "CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy";
				case 1 : return "CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy";
				case 2 : return "CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove";
			} break;
			// Tec3_1_1::MI_MobilityConcept
			case 315 :
			switch (t) {
				case 0 : return "MIMC_ConceptIncludesGoalsForSustainableMobility";
				case 1 : return "MIMC_ConceptIncludesFutureTrafficDemands";
			} break;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 :
			switch (t) {
				case 0 : return "IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage";
				case 1 : return "IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers";
			} break;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 :
			switch (t) {
				case 0 : return "IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft";
				case 1 : return "IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection";
				case 2 : return "IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection";
			} break;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 :
			switch (t) {
				case 0 : return "IMIT_ParkingSpacesReducedAccordingToRegulations";
				case 1 : return "IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds";
				case 2 : return "IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing";
				case 3 : return "IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant";
				case 4 : return "IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces";
			} break;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 :
			switch (t) {
				case 0 : return "IA2030MMC_MobilityConceptIncludesMobilityManagementConcept";
			} break;
			// Tec3_1_3::para_t
			case 320 :
			switch (t) {
				case 0 : return "Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots";
				case 1 : return "Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock";
				case 2 : return "Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock";
				case 3 : return "Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock";
				case 4 : return "Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock";
				case 5 : return "Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock";
			} break;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 :
			switch (t) {
				case 0 : return "IAFSBTEB_ResultsSubmitted";
			} break;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 :
			switch (t) {
				case 0 : return "IAFSMIT_ResultsSubmitted";
			} break;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 :
			switch (t) {
				case 0 : return "IAFSILTS_IntegrationIntoBuildingEnergyManagement";
				case 1 : return "IAFSILTS_IntegrationIntoLoadingManagementNetwork";
			} break;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 :
			switch (t) {
				case 0 : return "IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles";
			} break;
			// Tec3_1_4::para_t
			case 325 :
			switch (t) {
				case 0 : return "Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers";
			} break;
			// Tec3_1_4::RS_MobilitySharing
			case 326 :
			switch (t) {
				case 0 : return "RSMS_ResultsSubmitted";
				case 1 : return "RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems";
			} break;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 :
			switch (t) {
				case 0 : return "OCBGO_SufficientAvailabilityOfShowers";
				case 1 : return "OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear";
				case 2 : return "OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes";
				case 3 : return "OCBGO_Residential_ParkingSpacesForBikeTrailers";
			} break;
			// Technology::para_weights
			case 328 :
			switch (t) {
				case 0 : return "PW_Tec1_3";
				case 1 : return "PW_Tec1_4";
				case 2 : return "PW_Tec1_6";
				case 3 : return "PW_Tec3_1";
			} break;
			// Technology::para_goals
			case 329 :
			switch (t) {
				case 0 : return "PG_Tec1_3";
				case 1 : return "PG_Tec1_4";
				case 2 : return "PG_Tec1_6";
				case 3 : return "PG_Tec3_1";
			} break;
			// Utilities::UsageType
			case 330 :
			switch (t) {
				case 0 : return "offices";
				case 1 : return "education";
				case 2 : return "residential";
				case 3 : return "hotel";
				case 4 : return "convenienceStore";
				case 5 : return "shoppingCenter";
				case 6 : return "commercialBuilding";
				case 7 : return "logistics";
				case 8 : return "production";
				case 9 : return "assembly";
				case 10 : return "healthcare";
			} break;
		} // switch
		return INVALID_KEYWORD_INDEX_STRING;
	}

	const char * KeywordList::Description(const char * const enumtype, int t, bool * no_description) {
		if (no_description != nullptr)
			*no_description = false; // we are optimistic
		switch (enum2index(enumtype)) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCCPIES_Var1SubmissionOfCO2OrClimateCosts";
				case 1 : if (no_description != nullptr) *no_description = true; return "LCCCPIES_Var2SubmissionOfEcologicalSuggestions";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCCPICO_CalculationAndDisclosureOfConstructionAndUtilisationCosts";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCCPIPE_PartialExaminationsDuringLP2";
				case 1 : if (no_description != nullptr) *no_description = true; return "LCCCPIPE_PartialExaminationsDuringLP3";
				case 2 : if (no_description != nullptr) *no_description = true; return "LCCCPIPE_PartialExaminationsDuringLP4";
				case 3 : if (no_description != nullptr) *no_description = true; return "LCCCPIPE_FundingAdviceSessionByEndOfLP4";
				case 4 : if (no_description != nullptr) *no_description = true; return "LCCCPIPE_SubmissionOfClimateProtectionAgendaDiscussionWithOwner";
			} break;
			// Eco1_1_2::para_t
			case 3 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse";
			} break;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EECBOBEB_BuildingUpToInnovationClauseStandards";
				case 1 : if (no_description != nullptr) *no_description = true; return "EECBOBEB_AltBuildingReceivedKFWFundingForEnergyEfficiencyClassAOrBetter";
			} break;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EECBOCEBR_CircularEconomySolutionsForReuseSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "EECBOCEBR_LCCModelIncludesEndOfLifeCosts";
				case 2 : if (no_description != nullptr) *no_description = true; return "EECBOCEBR_DocumentationOfRawMaterialValue";
				case 3 : if (no_description != nullptr) *no_description = true; return "currentValue_eco1_1_2EECBOCEBR_NumberOfCircularEconomySolutionsForReuse";
			} break;
			// Eco1_1_3::para_t
			case 6 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeUpperValue";
				case 1 : if (no_description != nullptr) *no_description = true; return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeIntermediateValue";
				case 2 : if (no_description != nullptr) *no_description = true; return "ReferenceValue_eco1_1_3netLCCPerBuildingTypeLowerValue";
				case 3 : if (no_description != nullptr) *no_description = true; return "CurrentValue_eco1_1_3BRLCCC_NetLifeCycleCosts";
				case 4 : if (no_description != nullptr) *no_description = true; return "CurrentValue_eco1_1_3BRLCCC_CSAnnualEnergyConsumptionPerMeterRefrigeratedDC";
				case 5 : if (no_description != nullptr) *no_description = true; return "ReferenceValue_eco1_1_3BRLCCC_HealthCareTypeII";
			} break;
			// Eco1_1_3::BRLCC_Calculation
			case 7 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BRLCCC_NetLifeCycleCostsResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "BRLCCC_DisplayCaseFlag";
				case 2 : if (no_description != nullptr) *no_description = true; return "BRLCCC_HealthCareTypeIIFlag";
			} break;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ASBCSA_GeneralPerceptionOfSite";
				case 1 : if (no_description != nullptr) *no_description = true; return "ASBCSA_DemographicAndEconomicDevelopmentOfMacroSite";
				case 2 : if (no_description != nullptr) *no_description = true; return "ASBCSA_ImmediateNeighbourhood";
			} break;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ASBCBCS_ReactionOfBuildingConceptToSiteAnalysis";
				case 1 : if (no_description != nullptr) *no_description = true; return "ASBCBCS_UseAndProvisioningOfEnvironmentSynergyEffects";
			} break;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_PlanInvolvesRegionalAnalysisConductedByInterdisciplinaryTeam";
				case 1 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_ConceptInvolvesPatientAndPersonnelRoutes";
				case 2 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_ConceptInvolvesMaterialTransportAndStorageSpaces";
				case 3 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_ConceptInvolvesComplianceWithHygienicRequirements";
				case 4 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_ConceptInvolvesPositioningOfTechnicalUnitsInRegardToAccomodatedFunctionsAndMainBuilding";
				case 5 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_ConceptInvolvesConsiderationOfFutureUsageScenarios";
				case 6 : if (no_description != nullptr) *no_description = true; return "ASBCHCBCS_ConsiderationOfCatastrophicScenariosAndEnsuranceOfContinuedOperation";
			} break;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ATPUSPR_SameUsageType";
				case 1 : if (no_description != nullptr) *no_description = true; return "ATPUSPR_DifferentUsageType";
			} break;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ATPUSPAIF_CeilingHeight";
				case 1 : if (no_description != nullptr) *no_description = true; return "ATPUSPAIF_BuildingDepth";
				case 2 : if (no_description != nullptr) *no_description = true; return "ATPUSPAIF_FloorAllotment";
				case 3 : if (no_description != nullptr) *no_description = true; return "ATPUSPAIF_GroundPlanFlexibility";
				case 4 : if (no_description != nullptr) *no_description = true; return "ATPUSPAIF_Construction";
				case 5 : if (no_description != nullptr) *no_description = true; return "ATPUSPAIF_BuildingServices";
			} break;
			// Eco2_4_3::para_t
			case 13 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_eco2_4_3DegreeOfUseOrTenancy";
			} break;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DUTTCDUT_ResultsSubmitted";
			} break;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DUTTCCEUT_AtLeastOneUserOrTenantContributesToCircularEconomy";
			} break;
			// Eco2_4_4::para_t
			case 16 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_eco2_4_4RatioOfUsableSpaceToGroundSpace";
				case 1 : if (no_description != nullptr) *no_description = true; return "ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_lower";
				case 2 : if (no_description != nullptr) *no_description = true; return "ReferenceValueeco2_4_4RatioOfUsableSpaceToGroundSpace_upper";
			} break;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SERUSGS_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "SERUSGS_LogisticsAndProductionCostOptimisation";
				case 2 : if (no_description != nullptr) *no_description = true; return "SERUSGS_LogisticsAndProductionEnvironmentalOptimisation";
				case 3 : if (no_description != nullptr) *no_description = true; return "SERUSGS_LogisticsAndProductionSocialOptimisation";
			} break;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SEMUS_ConceptIncludesMultipleUseOfRelevantPortionOfSpace";
				case 1 : if (no_description != nullptr) *no_description = true; return "SEMUS_UseIncludesMultipleUseOfRelevantPortionOfSpace";
			} break;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SEA2030S_SubmissionAndImplementationOfSufficiencyStrategy";
			} break;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RAAEF_RiskAnalysisDuringEarlyPlanningPhases";
			} break;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RABCT_AspirationsForVerification";
				case 1 : if (no_description != nullptr) *no_description = true; return "RABCT_ImplementationOfStandards";
			} break;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030CDI_QualityOfInternetConnection";
			} break;
			// Eco2_4_7::A2030_Expandability
			case 23 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030E_Concept";
			} break;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030IA_AddressEffect";
			} break;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BCRMPVPrePH4_ConceptSubmitted";
			} break;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BCRMPVPostPH4_ConceptSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "BCRMPVPostPH4_ProofOfNoNegativeConcequences";
			} break;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030CBA_Evaluation";
			} break;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ACCQEM_RecommendedMeasuresToReduceClimateRisksImplemented";
				case 1 : if (no_description != nullptr) *no_description = true; return "ACCQEM_MeasuresImproveResilienceAndInlcudeReductionOfAllHighRiskFactors";
				case 2 : if (no_description != nullptr) *no_description = true; return "ACCQEM_MeasuresFurtherIncludeReductionOfAllModerateRiskFactors";
				case 3 : if (no_description != nullptr) *no_description = true; return "ACCQEM_MeasuresReduceProbableFutureRisksOnSite";
			} break;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ACCQIAM_PreferentialUseOfNaturalAndPassiveSolutions";
				case 1 : if (no_description != nullptr) *no_description = true; return "ACCQIAM_MeasuresInAccordanceWithLocalRegionalPlans";
				case 2 : if (no_description != nullptr) *no_description = true; return "ACCQIAM_MeasuresInAccordanceWithNationalStrategy";
				case 3 : if (no_description != nullptr) *no_description = true; return "ACCQIAM_SurveillanceOfImplementedOrPreparedMeasures";
				case 4 : if (no_description != nullptr) *no_description = true; return "ACCQIAM_RegulationOfRemedialMeasures";
			} break;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ACCGRED_EssentialMeasuresTaken";
				case 1 : if (no_description != nullptr) *no_description = true; return "ACCGRED_GeneralResilienceExists";
			} break;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ACCA2030HL_ProbableHighHeatLoad";
				case 1 : if (no_description != nullptr) *no_description = true; return "ACCA2030HL_MeasuresTakenToReduceHeatLoadRisksToHealth";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MAFERSCMAQ_PositiveInfluenceOnImmissionInVicinity";
				case 1 : if (no_description != nullptr) *no_description = true; return "MAFERSCMAQ_RiskAnalysisConducted";
				case 2 : if (no_description != nullptr) *no_description = true; return "MAFERSCMAQ_RiskAnalysisProtectionMeasuresImplemented";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MAFERSCMN_NoiseProtectionConstruction";
				case 1 : if (no_description != nullptr) *no_description = true; return "MAFERSCMN_InclusionOfNoiseProtectionGroundPlans";
				case 2 : if (no_description != nullptr) *no_description = true; return "MAFERSCMN_SurveyReportForBuildingAndSurroundingsOnOptimisationmeasures";
				case 3 : if (no_description != nullptr) *no_description = true; return "MAFERSCMN_OptimisationmeasuresImplemented";
			} break;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MAFERSRRR_RadonAccessPreventedOrHeavilyHindered";
			} break;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DCBCPD_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "DCBCPD_ModelMatchesBuildingAndWasHandedOverToClient";
				case 2 : if (no_description != nullptr) *no_description = true; return "DCBCPD_RelevantCertificationsAndCalculationsMatchBuilding";
			} break;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DCBCSBD_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "DCBCSBD_PartsCatalogueIncludesEcologicalBalanceData";
				case 2 : if (no_description != nullptr) *no_description = true; return "DCBCSBD_PartsCatalogueIncludesEcologicalProductInformation";
				case 3 : if (no_description != nullptr) *no_description = true; return "DCBCSBD_PartsCatalogueIncludesCircularPropertiesMatchingBuilding";
				case 4 : if (no_description != nullptr) *no_description = true; return "DCBCSBD_PartsCatalogueHandedOverToClient";
			} break;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DCBCEDBUM_BuildingRessourcePassIsPartOfSuperordinateDataBaseForUrbanMines";
			} break;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DCBA2030DF_DigitalFootprintHeavilyReduced";
			} break;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ODBUROMP_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "ODBUROMP_CompleteObjectDocumentationChecklistHandedOverToClient";
				case 2 : if (no_description != nullptr) *no_description = true; return "ODBUROMP_AllDataKeptOnFileForFiveYearsAndHandedOverToOperatorCompany";
			} break;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ODBUOFBM_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "ODBUOFBM_UpToDateCompleteOperatorFriendlyModelHandedOvertoOperatorCompany";
				case 2 : if (no_description != nullptr) *no_description = true; return "ODBUOFBM_LifeCycleGreenhouseGasAndEnergyBalanceIncludedOrPreparedForMonitoring";
			} break;
			// Eco2_7_3::PPBIM_Preparation
			case 41 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PPBIMP_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "PPBIMP_UseOfSharedDataEnvironment";
				case 2 : if (no_description != nullptr) *no_description = true; return "PPBIMP_NecessaryBasicDocuments";
				case 3 : if (no_description != nullptr) *no_description = true; return "PPBIMP_BIMCoordinatorSurveilingModelQuality";
				case 4 : if (no_description != nullptr) *no_description = true; return "PPBIMP_CompetenceCheckAndCoordinationOfBEP";
				case 5 : if (no_description != nullptr) *no_description = true; return "PPBIMP_BIMInformationRequirementsAndGoalsCommunicated";
			} break;
			// Eco2_7_3::PPBIM_Creation
			case 42 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PPBIMC_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "PPBIMC_Level0to1_CAD3D";
				case 2 : if (no_description != nullptr) *no_description = true; return "PPBIMC_Level2_BIM4to5D";
				case 3 : if (no_description != nullptr) *no_description = true; return "PPBIMC_Level3_IntegratedBIM6to7D";
			} break;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PPBIMSO_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "PPBIMSO_VariantsCalculatedAndDocumented";
			} break;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PPBIMCEBIM2FMOC_SustainableOperatorConcept";
			} break;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PPBIMA2030SC_ModelBasedBuildingSustainabilityCheckConducted";
			} break;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DTOPCHDBM_CalculationByBGFSmallerThan5000m2Method";
				case 1 : if (no_description != nullptr) *no_description = true; return "DTOPCHDBM_AsBuiltControlImplementedAndDocumented";
				case 2 : if (no_description != nullptr) *no_description = true; return "DTOPCHDBM_BuildingDocumentationOrModelHasAsBuiltQuality";
				case 3 : if (no_description != nullptr) *no_description = true; return "DTOPCHDBM_DigitalBuildingRessourcePassIsPartOfDigitalTwinAndAvailable";
			} break;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DTOPCEDPC_DigitalisationConducted";
			} break;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DCIBR_CompleteDocumentationOnRemovabilityHandedOverToClient";
			} break;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ACCDT_CircularDigitalTwinImplemented";
			} break;
			// Economy::para_weights
			case 50 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PW_Eco1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PW_Eco2_4";
				case 2 : if (no_description != nullptr) *no_description = true; return "PW_Eco2_6";
				case 3 : if (no_description != nullptr) *no_description = true; return "PW_Eco2_7";
			} break;
			// Economy::para_goals
			case 51 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PG_Eco1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PG_Eco2_4";
				case 2 : if (no_description != nullptr) *no_description = true; return "PG_Eco2_6";
				case 3 : if (no_description != nullptr) *no_description = true; return "PG_Eco2_7";
			} break;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2ESOE_HighEnergyStandard";
				case 1 : if (no_description != nullptr) *no_description = true; return "CO2ESOE_CO2NeutralOperation";
				case 2 : if (no_description != nullptr) *no_description = true; return "CO2ESOE_PreparedCO2NeutralOperation";
				case 3 : if (no_description != nullptr) *no_description = true; return "CO2ESOE_SufficiencyStandard";
			} break;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2ESFV_MaterialOptimization";
				case 1 : if (no_description != nullptr) *no_description = true; return "CO2ESFV_CO2ReducedMaterials";
				case 2 : if (no_description != nullptr) *no_description = true; return "CO2ESFV_LowTech";
				case 3 : if (no_description != nullptr) *no_description = true; return "CO2ESFV_CircularDesign";
				case 4 : if (no_description != nullptr) *no_description = true; return "CO2ESFV_Longevity";
			} break;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2PSOE_ElevatedEnergeticStandard";
				case 1 : if (no_description != nullptr) *no_description = true; return "CO2PSOE_NettoGreenhouseGasNeutralOperation";
				case 2 : if (no_description != nullptr) *no_description = true; return "CO2PSOE_SufficiencyStandard";
			} break;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2PSFV_MaterialOptimization";
				case 1 : if (no_description != nullptr) *no_description = true; return "CO2PSFV_CO2ReducedMaterials";
				case 2 : if (no_description != nullptr) *no_description = true; return "CO2PSFV_LowTech";
				case 3 : if (no_description != nullptr) *no_description = true; return "CO2PSFV_CircularDesign";
				case 4 : if (no_description != nullptr) *no_description = true; return "CO2PSFV_Longevity";
			} break;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2PSEO_LogisticsAndSiteOperationsOptimizedForEmission";
			} break;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2A2030IPB_IntegrationOfPreexistingBuilding";
			} break;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CO2A2030MO_ForEmission";
			} break;
			// Env1_1_2::para_t
			case 59 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_2_2_1				[-]		// ToDo Einheit kg/m2a";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_2_2_1	[-]		// ToDo Einheit kg/m2a";
				case 2 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_2_5_1				[-]		// ToDo Einheit kg/m2a";
				case 3 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_2_5_1	[-]		// ToDo Einheit kg/m2a";
			} break;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCO2Disc_GreenHouseGasBalance";
				case 1 : if (no_description != nullptr) *no_description = true; return "LCCO2Disc_NonRenewablePrimaryEnergyBalance";
			} break;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCO2IER_ResultsSubmitted";
			} break;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCO2A2030LCCPA_AgendaSubmitted";
			} break;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCO2A2030CPTS_AgendaSubmitted";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCO2BFO_ClimateProtectionAgendaClimateNeutralOperation";
				case 1 : if (no_description != nullptr) *no_description = true; return "LCCO2BFO_AmbitiousClimateProtectionAgenda";
				case 2 : if (no_description != nullptr) *no_description = true; return "LCCO2BFO_NetGreenhouseHeutrallyClimateNeutrallyOperatedBuilding";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LCCO2BFSCO2RCP_ResultsSubmitted";
			} break;
			// Env1_1_3::para_t
			case 66 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_3_1_1					[-]		// ToDo Einheit kWh/m2a";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_3_1_1		[-]		// ToDo Einheit kWh/m2a";
				case 2 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_3_1_2POCP				[-]		// ToDo Einheit C2H4e/m2a";
				case 3 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_3_1_2POCP	[-]		// ToDo Einheit C2H4e/m2a";
				case 4 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_3_1_2AP				[-]		// ToDo Einheit SO2e/m2a";
				case 5 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_3_1_2AP		[-]		// ToDo Einheit SO2e/m2a";
				case 6 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_3_1_2EP				[-]		// ToDo Einheit PO43/m2a";
				case 7 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_3_1_2EP		[-]		// ToDo Einheit PO43/m2a";
				case 8 : if (no_description != nullptr) *no_description = true; return "RefEnv1_1_3_1_2FW				[-]		// ToDo Einheit m3/m2a";
				case 9 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_1_3_1_2FW		[-]		// ToDo Einheit m3/m2a";
			} break;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CVAEILCPEB_ResultsSubmitted";
			} break;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CVAEIWRAEI_ResultsSubmitted";
			} break;
			// Env1_2_1::para_t
			case 69 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EFMA2030_MeasurementsTakenForSufficientStructureNumberOfRows";
				case 1 : if (no_description != nullptr) *no_description = true; return "EFMA2030_WaivingOfUnsolveableConnectionsNumberOfRows";
			} break;
			// Env1_2_1::EFM_A
			case 70 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EFMA_QS1SimplifiedDocumentation";
				case 1 : if (no_description != nullptr) *no_description = true; return "EFMA_QS2SimplifiedDocumentation";
				case 2 : if (no_description != nullptr) *no_description = true; return "EFMA_QS2MaterialEcologicalComponentCatalogue";
				case 3 : if (no_description != nullptr) *no_description = true; return "EFMA_QS3MaterialEcologicalComponentCatalogue";
				case 4 : if (no_description != nullptr) *no_description = true; return "EFMA_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EFMBRC_QS1SimplifiedDocumentation";
				case 1 : if (no_description != nullptr) *no_description = true; return "EFMBRC_QS2SimplifiedDocumentation";
				case 2 : if (no_description != nullptr) *no_description = true; return "EFMBRC_QS2MaterialEcologicalComponentCatalogue";
				case 3 : if (no_description != nullptr) *no_description = true; return "EFMBRC_QS3MaterialEcologicalComponentCatalogue";
				case 4 : if (no_description != nullptr) *no_description = true; return "EFMBRC_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EFMBSC_QS1SimplifiedDocumentation";
				case 1 : if (no_description != nullptr) *no_description = true; return "EFMBSC_QS2SimplifiedDocumentation";
				case 2 : if (no_description != nullptr) *no_description = true; return "EFMBSC_QS2MaterialEcologicalComponentCatalogue";
				case 3 : if (no_description != nullptr) *no_description = true; return "EFMBSC_QS3MaterialEcologicalComponentCatalogue";
				case 4 : if (no_description != nullptr) *no_description = true; return "EFMBSC_QS4MaterialEcologicalComponentCatalogue";
			} break;
			// Env1_2_1::EFM_Agenda2030
			case 73 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EFMA2030_1WaivingOfCrossOutCriterionQS3";
				case 1 : if (no_description != nullptr) *no_description = true; return "EFMA2030_2WaivingOfCrossOutCriterionQS4";
				case 2 : if (no_description != nullptr) *no_description = true; return "EFMA2030_MeasurementsTakenForSufficientStructure";
				case 3 : if (no_description != nullptr) *no_description = true; return "EFMA2030_WaivingOfUnsolveableConnections";
				case 4 : if (no_description != nullptr) *no_description = true; return "EFMA2030_AllRowsOnlyFeatureProductsOfSVHCOfMax0_1Percent";
			} break;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EFMEPQS123_RealizationOfCoolingSystemWithoutHalogenatedCoolingAgent";
			} break;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RURPESCD_DeclarationOfDiligenceGiven";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RURPERURP_RegularIntegrationOfMeasures";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RURPERURED_PartsCatalogue";
			} break;
			// Env1_3_2::para_t
			case 78 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Env1_3_2_1NumberOfPartsFromDiffManufacturers";
				case 1 : if (no_description != nullptr) *no_description = true; return "ReferenceValueEnv1_3_2_2RRMRRWPSR_WeightingCostGroup";
				case 2 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS4";
				case 3 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_3_2_2RRMRRWPSR_DetailedMethodSumOfMassPercentOfPartsOfQS2";
				case 4 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS4";
				case 5 : if (no_description != nullptr) *no_description = true; return "CurrentValueEnv1_3_2_2RRMRRWPSR_SimplifiedMethodSumOfNumberOfPartsOfQS2";
			} break;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RRMCRRM_ResultSumbitted";
			} break;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RRMRRWPSR_DetailedMethod";
				case 1 : if (no_description != nullptr) *no_description = true; return "RRMRRWPSR_SimplifiedMethod";
			} break;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RRMPWMSF_PercentageMinimum50";
			} break;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RRMPRCEWMPS_Percentage";
			} break;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVSCWU_ConceptDevelopedInEarlyPlanningStage";
				case 1 : if (no_description != nullptr) *no_description = true; return "DWDWWVSCWU_FlowClassesOfSanitaryEquipment";
				case 2 : if (no_description != nullptr) *no_description = true; return "DWDWWVSCWU_LocalWaterUsageIndex";
				case 3 : if (no_description != nullptr) *no_description = true; return "DWDWWVSCWU_PotentialOfRainAndGrayWaterUsage";
				case 4 : if (no_description != nullptr) *no_description = true; return "DWDWWVSCWU_EfficentWateringOfOutsideAreas";
				case 5 : if (no_description != nullptr) *no_description = true; return "DWDWWVSCWU_EdequatePlanningOfWaterUsageMeteringPoint";
			} break;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVUSC_ConceptUpdatedToPlanningProgress";
				case 1 : if (no_description != nullptr) *no_description = true; return "DWDWWVUSC_ImplementationOfDemonstrablyRelevantAspects";
			} break;
			// Env2_2_2::para_t
			case 85 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_2WaterUsageIndex";
				case 1 : if (no_description != nullptr) *no_description = true; return "RefValue_env2_2DWDWWVWUI_DynamicThreshold";
			} break;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVWUI_ResultsSubmitted";
			} break;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVIR_NoPlannedIrrigationWithDrinkingWater";
				case 1 : if (no_description != nullptr) *no_description = true; return "DWDWWVIR_OutsideAreasIncludeRainwaterIrrigationSetup";
			} break;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVDIQI_DegreeOfIntegrationIntoPreexistingInfrastructureAndUseOfSeparationReductionEtc";
			} break;
			// Env2_2_5::para_t
			case 89 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_2DWDWWVSC_WaterEconomyTotalDeviation";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_2DWDWWVSC_DeviationFromEvaporationPortion";
				case 2 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_2DWDWWVSC_DeviationFromInfiltrationPortion";
			} break;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVSC_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "DWDWWVSC_InfiltrationPossible";
				case 2 : if (no_description != nullptr) *no_description = true; return "DWDWWVSC_UndercuttingTheDrainagePortion";
			} break;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DWDWWVDWS_LowEnergyDrinkingWaterManagementSystem";
				case 1 : if (no_description != nullptr) *no_description = true; return "DWDWWVDWS_ObservationOfDrinkingWaterSanitation";
				case 2 : if (no_description != nullptr) *no_description = true; return "DWDWWVDWS_WarmWaterReducedToOperativeMinimum";
				case 3 : if (no_description != nullptr) *no_description = true; return "DWDWWVDWS_ColdWaterLessThan20Degrees";
			} break;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ADDC_OutlyingDevelopmentArea";
				case 1 : if (no_description != nullptr) *no_description = true; return "ADDC_InternalDevelopmentArea";
				case 2 : if (no_description != nullptr) *no_description = true; return "ADDC_DevelopmentAreaInPriorStructuralOrInfrastructuralUse";
			} break;
			// Env2_3_2::para_t
			case 93 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_3_2ADDSAM_DegreeOfSealing";
			} break;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ADDSAM_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "ADDSAM_ImplementationOfAdjustmentMeasures";
			} break;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ADCEBU_30PercentOfAreaUnsealedPreConstruction";
			} break;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ADSQISR_ExaminationOfSiteAndPreexistingBuildingForContamination";
				case 1 : if (no_description != nullptr) *no_description = true; return "ADSQISR_LowContaminationRecyclingAndDisposal";
				case 2 : if (no_description != nullptr) *no_description = true; return "ADSQISR_HighContaminationDisposal";
			} break;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ADSQICEBISSRS_InSituRestorationChemicalOrBiologicalNoSoilExchange";
				case 1 : if (no_description != nullptr) *no_description = true; return "ADSQICEBISSRS_LowDegreeOfTransformationOfSoilAndSafeguardingOfContaminants";
				case 2 : if (no_description != nullptr) *no_description = true; return "ADSQICEBISSRS_RestorationOfGroundWaterDamages";
			} break;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSCEBDS_ExtensiveAndLongTermStrategy";
			} break;
			// Env2_4_2::para_t
			case 99 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_4_2BDOSBBSA_PercentageOfBiodiversitySupportingOutdoorArea";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_4_2BDOSBGR_PercentageOfGreenRoof";
				case 2 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_4_2BDOSBAFA2030VB_BFFOfSite";
			} break;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSBBSA_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSBGR_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSBAFA2030VB_ResultsSubmitted";
			} break;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSDS_StructureTypesEmbeddedInBiodiversitySupportingConcept";
				case 1 : if (no_description != nullptr) *no_description = true; return "BDOSDS_TwoBiotopeStructureTypesAvailable";
			} break;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSA2030FS_EmploymentOfSOTAMethodsForImprovementOfSoilQualityAndCultivationOfHumus";
			} break;
			// Env2_4_3::para_t
			case 105 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_env2_4_3BDOSVEDLSSS_SelectionIsLocalDiverseAndSuitedToSitePointResult";
			} break;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSVNEIPS_NoFurtherEmploymentOfInvasivePlantSpecies";
				case 1 : if (no_description != nullptr) *no_description = true; return "BDOSVNEIPS_PlanForControlOfPreexistingInvasiveSpecies";
			} break;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSVEDLSSS_SelectionBasedOnBiodiversitySupportingConcept";
				case 1 : if (no_description != nullptr) *no_description = true; return "BDOSVEDLSSS_ResultSubmitted";
			} break;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSVA2030PVHEV_PreservationOfSaidVegetationDuringConstructionAndAfter";
			} break;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSRSBI_ConceptDeveloped";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSRNIIC_IlluminationConceptForAvoidanceOfLightPollution";
				case 1 : if (no_description != nullptr) *no_description = true; return "BDOSRNIIC_HarmlessLightSourceOrientation";
				case 2 : if (no_description != nullptr) *no_description = true; return "BDOSRNIIC_HarmlessLightColourAndLightSourceTemperature";
				case 3 : if (no_description != nullptr) *no_description = true; return "BDOSRNIIC_NoUnwantedBlindingEffects";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSRNIAT_EvaluationOfDangersToAnimals";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSRNICSP_AccordanceWithEnvironmentProtectionAndBiodiversityInterests";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSPCMDMCC_ContractSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "BDOSPCMDMCC_EcologicalCarePlanSubmitted";
				case 2 : if (no_description != nullptr) *no_description = true; return "BDOSPCMDMCC_NoUseOfTurfMaterials";
				case 3 : if (no_description != nullptr) *no_description = true; return "BDOSPCMDMCC_NoUseOfHerbicidesOnSite";
				case 4 : if (no_description != nullptr) *no_description = true; return "BDOSPCMDMCC_NoUseOfBiocidesOnSite";
				case 5 : if (no_description != nullptr) *no_description = true; return "BDOSPCMDMCC_NoUseOfChemicalFertiliserOnSite";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSPCMMSC_SimpleMonitoringOfNestingAids";
				case 1 : if (no_description != nullptr) *no_description = true; return "BDOSPCMMSC_ExtensiveMonitoring";
			} break;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BDOSAC_AlternativeCertificationSubmitted";
			} break;
			// Environment::para_weights
			case 116 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PW_Env1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PW_Env1_2";
				case 2 : if (no_description != nullptr) *no_description = true; return "PW_Env1_3";
				case 3 : if (no_description != nullptr) *no_description = true; return "PW_Env2_2";
				case 4 : if (no_description != nullptr) *no_description = true; return "PW_Env2_3";
				case 5 : if (no_description != nullptr) *no_description = true; return "PW_Env2_4";
			} break;
			// Environment::para_goals
			case 117 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PG_Env1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PG_Env1_2";
				case 2 : if (no_description != nullptr) *no_description = true; return "PG_Env1_3";
				case 3 : if (no_description != nullptr) *no_description = true; return "PG_Env2_2";
				case 4 : if (no_description != nullptr) *no_description = true; return "PG_Env2_3";
				case 5 : if (no_description != nullptr) *no_description = true; return "PG_Env2_4";
			} break;
			// KeywordList::MyParameters
			case 118 :
			switch (t) {
				case 0 : return "Some temperatures";
				case 1 : return "Some mass";
			} break;
			// Pro1_1_1::RP_Basis
			case 119 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RPB_ImplementationOfDeclarationSustainabilityArchitecture";
				case 1 : if (no_description != nullptr) *no_description = true; return "RPB_ComplianceWithEuropeanSustainableReportFrameworkLevels";
			} break;
			// Pro1_1_1::RP_RP
			case 120 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RPRP_PlanFollowsChecklist1OrAnnexe1A";
				case 1 : if (no_description != nullptr) *no_description = true; return "RPRP_PlanFollowsChecklist12OrAnnexe1B";
				case 2 : if (no_description != nullptr) *no_description = true; return "RPRP_PlanFollowsChecklist123OrAnnexe1C";
			} break;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RPA2030FS_FeasibilitySurveyConductedAllowingForImplementationOfSustainableConcepts";
			} break;
			// Pro1_1_2::A2030_Participation
			case 122 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030P_CounselDuringRequirementAnalysis";
				case 1 : if (no_description != nullptr) *no_description = true; return "A2030P_ParticipationDuringRequirementAnalysis";
				case 2 : if (no_description != nullptr) *no_description = true; return "A2030P_CounselDuringConceptionPhase";
				case 3 : if (no_description != nullptr) *no_description = true; return "A2030P_ParticipationDuringConceptionPhase";
				case 4 : if (no_description != nullptr) *no_description = true; return "A2030P_CounselDuringImplementationPhase";
				case 5 : if (no_description != nullptr) *no_description = true; return "A2030P_ParticipationDuringImplementationPhase";
			} break;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CSSR_SpecificationsIncludeDetailedRequirementsToBuildingsSustainabilityFromEcologicalEconomicalSocioculturalFunctionalTechnicalAspectsAsWellAsPlanningAndConstructionPhase";
				case 1 : if (no_description != nullptr) *no_description = true; return "CSSR_SpecificationsFurtherIncludeDefinitionsOfResponsibilitiesAndPlanningMethodAndEssentialPlanningPhasesDecidedByAPlanningTeam";
			} break;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SATOEI_SelectSustainabilityAspectsOfHealthCompatibilityOrEnvironmentCompatibilityOrRelevantTechnicalAspectsIncludedInOffersGeneralPreliminaryRemarks";
				case 1 : if (no_description != nullptr) *no_description = true; return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedInOffersGeneralPreliminaryRemarks";
				case 2 : if (no_description != nullptr) *no_description = true; return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer";
				case 3 : if (no_description != nullptr) *no_description = true; return "SATOEI_RequirementsToHealthCompatibilityOrEnvironmentCompatibilityAndTechnicalAspectsOfConstructionProductsIncludedCraftSpecificallyAndSelectivelyOnAServiceItemLevelInOffer";
			} break;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SATOCERM_NoExclusionOfRecycledMaterialsInTenderOffer";
			} break;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVPEVPC_PreemptiveExaminationButNoPlanningCompetitionConducted";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVCAMSM_ImplementationOfConceptAssignment";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVCAMSM_ImplementationOfConceptAssignmentWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVCAQE_CompetentDecisionMakingBoard";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVCAQE_PostProcedureQualityEnsurance";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVMASM_ImplementationOfMultipleAssignments";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVMASM_ImplementationOfMultipleAssignmentsWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVMAQE_CompetentDecisionMakingBoardOrSupervisionBySuch";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5";
				case 2 : if (no_description != nullptr) *no_description = true; return "CEVMAIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVPCSQM_ImplementationOfPlanningCompetition";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVPCSQM_ImplementationOfPlanningCompetitionWithSpecialConcernForSustainableConstruction";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVPCMCM_CooperativeMethod";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVPCMCM_OneOrTwoPhases_OpenCompetitionOrClosedCompetitionWithPreliminaryRound";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH3";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH5";
				case 2 : if (no_description != nullptr) *no_description = true; return "CEVPCIAWD_CommissioningOfAwardWinnerAndImplementationOfDesignUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH3";
				case 1 : if (no_description != nullptr) *no_description = true; return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH5";
				case 2 : if (no_description != nullptr) *no_description = true; return "CEVPCCAWPT_CommissioningOfAwardWinnersPlanningTeamUntilAtLeastHOAI_LPH8";
			} break;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RIDB_ProjectPresentationInFrontOfDesignBoardOfCommuneAndArchitecturalAssociation";
				case 1 : if (no_description != nullptr) *no_description = true; return "RIDB_ImplementationOfDesignBoardsRecommendations";
			} break;
			// Pro1_6_3::HAA_Recognition
			case 137 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "HAAR_RecognitionOfGoodConstructionalCulturalQuality";
				case 1 : if (no_description != nullptr) *no_description = true; return "HAAR_RecognitionOfFinishedProjectWithArchitectureAwardDGNBDiamond";
			} break;
			// Pro2_1_1::NRCS_Concept
			case 138 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "NRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "NRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "NRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_2::DRCS_Concept
			case 141 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_3::SGPCS_Concept
			case 144 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SGPCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SGPCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SGPCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_4::WRCS_Concept
			case 147 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "WRCSC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "WRCSIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "WRCSEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "WRCSCEWP_UseOfNovelAndLargelyWastePreventiveConceptsMethodsAndTechnologies";
			} break;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CESI_NotificationOfNearbyResidentsOnProjectAndSite";
			} break;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CECR_DetailsOnHowResidentsAreInformedOnAndIncludedInProjectAsideFromSignage";
			} break;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CISI_ParticipantsInProjectProvidedWithAllRelevantInformation";
				case 1 : if (no_description != nullptr) *no_description = true; return "CISI_GuaranteeOfFixedInformationFlowBetweenPlannersAndSite";
				case 2 : if (no_description != nullptr) *no_description = true; return "CISI_ContinuousCommunicationOfRelevantInformationOnConstructionProgress";
				case 3 : if (no_description != nullptr) *no_description = true; return "CISI_AvailabilityOfCompleteAndUpToDateListsOfProvidersPlannersAndConstructors";
				case 4 : if (no_description != nullptr) *no_description = true; return "CISI_OnlineAvailabilityOfAllInformation";
			} break;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCWUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite";
			} break;
			// Pro2_1_6::RCWU_Concept
			case 155 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCWUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCWUIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCWUEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCEUDT_MeasuringAndDocumentationOfWaterUsageOnConstructionSite";
			} break;
			// Pro2_1_6::RCEU_Concept
			case 159 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCEUC_CompilationOfConceptIncludingIdentificationOfRelevantCrafts";
			} break;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCEUIO_InstructionOrBriefungOfOperators";
			} break;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RCEUEI_ExaminationOrVerificationOfImplementation";
			} break;
			// Pro2_1_7::M_Prevention
			case 162 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MP_CreationAndImplementationOfAnAerationProgrammSuitedToConstructionSituationGuaranteeingSufficientDryingOutOfSite";
			} break;
			// Pro2_3_1::TM_PlanningPhase
			case 163 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TMPP_DesignOfAMonitoringConceptIncludingEnergeticMonitoring";
				case 1 : if (no_description != nullptr) *no_description = true; return "TMPP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TMCP_ContinuationOfAMonitoringConcept";
				case 1 : if (no_description != nullptr) *no_description = true; return "TMCP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_3::TrialOperation
			case 165 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TO_TrialOperationConductedPriorToApprovalAndHandover";
				case 1 : if (no_description != nullptr) *no_description = true; return "TO_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TMFOP_AssignmentOfARegulationMonitoringToOptimiseOperation";
				case 1 : if (no_description != nullptr) *no_description = true; return "TMFOP_CertifiedAlternativeSolution";
			} break;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TMCM_AssignmentOfACompleteTechnicalMonitoring";
			} break;
			// Pro2_3_6::OperationStartUpManagement
			case 168 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "OSUM_StartUpManagementInAdditionToTechnicalManagement";
			} break;
			// Pro2_3_7::BuildingPerformance
			case 169 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BP_AssignmentOfContinuousImprovementProcessAfterHandover";
			} break;
			// Pro2_5_1::FM_Check
			case 170 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "FMC_ConductionWithRegardToAccessibilityOperationRoutingAndAreaUsage";
			} break;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MIOSI_CreationOfInstructionsAndHandoverToHiredServiceCompaniesOrConductors";
				case 1 : if (no_description != nullptr) *no_description = true; return "MIOSI_CreationOfMaintenanceAndUpkeepPlansForHighCareElementsOfCostGroups300And400";
				case 2 : if (no_description != nullptr) *no_description = true; return "MIOSI_IncorporationOfGuidelinesForSustainableBuildingOperation";
			} break;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "FMG_CreationAndHandoverToFacilityManager";
			} break;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CWU_CreationAndHandoverTechnicalOperationHandbook";
				case 1 : if (no_description != nullptr) *no_description = true; return "CWU_PreparationAndHandoverOfQuestionaryOnUserSatisfactionDuringOperationPhase";
			} break;
			// Pro2_5_5::SIS_Implementation
			case 174 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SISI_CreationOfConceptIncludingImplementationPlan";
				case 1 : if (no_description != nullptr) *no_description = true; return "SISI_InstallationOfSustainabilityInformationSystem";
			} break;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SISA2030NEKI_InfluenceOfNatureExperienceAndKnowledgeImpartationOnOutdoorAreaDesignConcept";
				case 1 : if (no_description != nullptr) *no_description = true; return "SISA2030NEKI_AppealingOfferForUsersToExperienceNatureWithAllOrSeveralSenses";
			} break;
			// Pro2_5_6::OCP_Extended
			case 176 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "OCPE_CreationOfExtendedOperationCostPrognosis";
			} break;
			// Process::para_weights
			case 177 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PW_Pro1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PW_Pro1_4";
				case 2 : if (no_description != nullptr) *no_description = true; return "PW_Pro1_6";
				case 3 : if (no_description != nullptr) *no_description = true; return "PW_Pro2_1";
				case 4 : if (no_description != nullptr) *no_description = true; return "PW_Pro2_3";
				case 5 : if (no_description != nullptr) *no_description = true; return "PW_Pro2_5";
			} break;
			// Process::para_goals
			case 178 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PG_Pro1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PG_Pro1_4";
				case 2 : if (no_description != nullptr) *no_description = true; return "PG_Pro1_6";
				case 3 : if (no_description != nullptr) *no_description = true; return "PG_Pro2_1";
				case 4 : if (no_description != nullptr) *no_description = true; return "PG_Pro2_3";
				case 5 : if (no_description != nullptr) *no_description = true; return "PG_Pro2_5";
			} break;
			// Site::para_weights
			case 179 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PW_Site1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PW_Site1_3";
				case 2 : if (no_description != nullptr) *no_description = true; return "PW_Site1_4";
			} break;
			// Site::para_goals
			case 180 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PG_Site1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PG_Site1_3";
				case 2 : if (no_description != nullptr) *no_description = true; return "PG_Site1_4";
			} break;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRCA_ConductionOfAnalysis";
				case 1 : if (no_description != nullptr) *no_description = true; return "CRCA_ConductionOfQualifiedAnalysisByExperts";
			} break;
			// Site1_1_1::CR_Screening
			case 182 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRS_AppendixA3TableA";
				case 1 : if (no_description != nullptr) *no_description = true; return "CRS_AppendixA3TableB";
				case 2 : if (no_description != nullptr) *no_description = true; return "CRS_AdditionallyAppendixA3TableC";
			} break;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext10To25Years";
				case 1 : if (no_description != nullptr) *no_description = true; return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheNext26To50Years";
				case 2 : if (no_description != nullptr) *no_description = true; return "CRSEP_AnalysisEvaluatesClimateDevelopmentOverTheEntireBuildingLifeExpectancy";
			} break;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRAT_EvaluationOfEnvironmentAndClimateHazardProbability";
				case 1 : if (no_description != nullptr) *no_description = true; return "CRAT_Vulnerability_EvaluationOfImpactOnBuildingOperationUsersAndAssetValue";
			} break;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRA2030CPG_ConsiderationOfSurroundingConditionsAndAdaptationSolutionsOfOthers";
			} break;
			// Site1_1_1::CR_DataBasis
			case 186 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRDB_DamageProbabilityEvaluationBasedOnIPCCAssessmentReportWorstCaseScenarioRCP85";
				case 1 : if (no_description != nullptr) *no_description = true; return "CRDB_AdditionallyScenarioRCP6_0";
				case 2 : if (no_description != nullptr) *no_description = true; return "CRDB_AdditionallyScenarioRCP4_5";
				case 3 : if (no_description != nullptr) *no_description = true; return "CRDB_AdditionallyScenarioRCP2_6";
			} break;
			// Site1_1_1::CR_ResultApplication
			case 187 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CRRA_PhysicalRiskAndVulnerabilityAnalysisConductedPreConstruction";
			} break;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ECRSCFPRECC_DeterminedRisksAndVulnerabilitiesOnSiteExclusivelyMinorToOperationUsersAndAssetValue";
			} break;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan75dB";
				case 1 : if (no_description != nullptr) *no_description = true; return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan65dB";
				case 2 : if (no_description != nullptr) *no_description = true; return "EEISN_EvaluationOfSurroundingNoiseLevelBasedOnExistingNoiseLevelAccordingToDIN4109_LessThan55dB";
			} break;
			// Site1_1_3::EEI_AirQuality
			case 190 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EEIAQ_PM10ExceedsLimitOnNoMoreThan35DaysAnnually";
				case 1 : if (no_description != nullptr) *no_description = true; return "EEIAQ_PM10NeverExceedsLimit";
				case 2 : if (no_description != nullptr) *no_description = true; return "EEIAQ_PM2_5NeverExceedsLimit";
				case 3 : if (no_description != nullptr) *no_description = true; return "EEIAQ_NO2ExceedsLimitOnNoMoreThan18IntervalsOf3HoursBeyondThe1HourDailyLimitAnnually";
				case 4 : if (no_description != nullptr) *no_description = true; return "EEIAQ_NO2NeverExceedsExceedsLimit";
			} break;
			// Site1_1_3::EEI_Radon
			case 191 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "EEIR_ExaminationIfSiteIsInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation";
				case 1 : if (no_description != nullptr) *no_description = true; return "EEIR_ConclusionThatSiteIsNotInARadonPreventionZoneBasedOnZonePassOrGovernmentalInformation";
				case 2 : if (no_description != nullptr) *no_description = true; return "EEIR_RadonConcentrationOfCompartmentOrBasementAirMeasured";
				case 3 : if (no_description != nullptr) *no_description = true; return "EEIR_ReferenceValueMeasuredOrExpectedInLessThan75PercentOfAdministrationUnitZoneOrNoMoreThan10PercentOfBuildings";
			} break;
			// Site1_3_1::MIT_Surroundings
			case 192 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MITS_ConnectionToBundesstrasseA_Road";
				case 1 : if (no_description != nullptr) *no_description = true; return "MITS_ConnectionToFreeway";
				case 2 : if (no_description != nullptr) *no_description = true; return "MITS_ConnectionToMainStreet";
			} break;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MITRB_BuildingParkingSpacesAreIntegratedIntoSuperordinateParkingConceptOfParkingAreasUsedMostlyByUserGroupsOfSeveralBuildingsInTheQuarter";
			} break;
			// Site1_3_2::PT_Stations
			case 194 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PTS_DistancedWithin350Meters";
			} break;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PTDTSHD_NoMoreThan20Minutes";
				case 1 : if (no_description != nullptr) *no_description = true; return "PTDTSHD_NoMoreThan15Minutes";
				case 2 : if (no_description != nullptr) *no_description = true; return "PTDTSHD_NoMoreThan10Minutes";
			} break;
			// Site1_3_2::PT_Intervals
			case 196 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PTI_NoMoreThan15Minutes";
				case 1 : if (no_description != nullptr) *no_description = true; return "PTI_NoMoreThan10Minutes";
				case 2 : if (no_description != nullptr) *no_description = true; return "PTI_NoMoreThan5Minutes";
			} break;
			// Site1_3_2::PT_RelationToBuilding
			case 197 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PTRB_BuildingBulletinBoardOrSimilarFeaturesNearbyStationSchedulesOrDigitalDisplay";
				case 1 : if (no_description != nullptr) *no_description = true; return "PTRB_BuildingBulletinBoardOrSimilarFeaturesPlanOfSurroundingsWithStationsAndDistances";
				case 2 : if (no_description != nullptr) *no_description = true; return "PTRB_BuildingFeaturesSignageToStations";
			} break;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BTCT500M_PartialMixWithMotorTraffic";
				case 1 : if (no_description != nullptr) *no_description = true; return "BTCT500M_NoMixWithMotorTrafficOrSharedSpaceOrCycleTracks";
			} break;
			// Site1_3_3::BT_Connection
			case 199 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BTC_ContinuousRegionalConnection";
				case 1 : if (no_description != nullptr) *no_description = true; return "BTC_ContinuousInterregionalConnectionMoreThan10KM";
			} break;
			// Site1_3_3::BT_RelationToBuilding
			case 200 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BTRB_RoutingOnSiteAllowsRidingUpToBuildingOrBicycleRacks";
			} break;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "FTWN350M_50PercentOrMoreCoverage";
				case 1 : if (no_description != nullptr) *no_description = true; return "FTWN350M_80PercentOrMoreCoverage";
				case 2 : if (no_description != nullptr) *no_description = true; return "FTWN350M_100PercentCoverage";
			} break;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "FTCO350M_80PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach";
				case 1 : if (no_description != nullptr) *no_description = true; return "FTCO350M_100PercentOfStreetsAreSafeToCrossAndCrossingsAreSafeToReach";
			} break;
			// Site1_3_4::FT_SignageSystems
			case 203 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "FTSS_SignageCoversSurroundingArea";
				case 1 : if (no_description != nullptr) *no_description = true; return "FTSS_SignageAndOrientationPlansCoverSurroundingArea";
			} break;
			// Site1_3_5::AS_Within350Meters
			case 204 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ASW350M_80PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots";
				case 1 : if (no_description != nullptr) *no_description = true; return "ASW350M_100PercentOfWalkwaysBetweenEntranceAndStationFeatureHeightDifferencesSmallerThan3cmAndMarkedBoardingSpots";
			} break;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ASADRBS_TactileGuidingElementsPrivateWalkwayLoweringsAndCrossingsSeparatedFromCycletracksNoSightObstructionOrStairs";
			} break;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030UPLI_PublicLoadingInfrastructureForMotorisedIndividualTransportWithin350Meters";
			} break;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SIQS_DaycareWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters";
				case 1 : if (no_description != nullptr) *no_description = true; return "SIQS_SecondaryOrVocationalSchoolWithin15MinutesOnFootOrByPublicTransportAndWithin1300Meters";
				case 2 : if (no_description != nullptr) *no_description = true; return "SIQS_CinemaTheatreOrGalleryWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 3 : if (no_description != nullptr) *no_description = true; return "SIQS_BookstoreWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 4 : if (no_description != nullptr) *no_description = true; return "SIQS_QuarterCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 5 : if (no_description != nullptr) *no_description = true; return "SIQS_ParishHallWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 6 : if (no_description != nullptr) *no_description = true; return "SIQS_YouthCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 7 : if (no_description != nullptr) *no_description = true; return "SIQS_ElderlyCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 8 : if (no_description != nullptr) *no_description = true; return "SIQS_FitnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 9 : if (no_description != nullptr) *no_description = true; return "SIQS_PubliclyAccessibleFitnessProgramInTheBuildingAndOpenToExternalUsers";
				case 10 : if (no_description != nullptr) *no_description = true; return "SIQS_PlaygroundWithin5MinutesOnFootOrByPublicTransportAndWithin350Meters";
				case 11 : if (no_description != nullptr) *no_description = true; return "SIQS_GymSportsFieldOrSwimmingPoolWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
			} break;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SIOUIOBS_ThirdPartiesHaveTheOptionToRentBuildingSpacesTemporarily";
				case 1 : if (no_description != nullptr) *no_description = true; return "SIOUIOBS_SC_NeccessaryRoutingAccessibleOutsideOfBusinessHours";
				case 2 : if (no_description != nullptr) *no_description = true; return "SIOUIOBS_OutdoorBuildingSpacesAccessibleToPublicAtAllTimes";
			} break;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "POEIQS_LocalAmeneties1_ShoppingCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 1 : if (no_description != nullptr) *no_description = true; return "POEIQS_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 2 : if (no_description != nullptr) *no_description = true; return "POEIQS_LocalAmeneties3_FarmersMarketWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 3 : if (no_description != nullptr) *no_description = true; return "POEIQS_Gastronomy_RestaurantCafeBakeryEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 4 : if (no_description != nullptr) *no_description = true; return "POEIQS_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenterWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 5 : if (no_description != nullptr) *no_description = true; return "POEIQS_Healthcare1_GeneralPractitionerWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
				case 6 : if (no_description != nullptr) *no_description = true; return "POEIQS_Healthcare2_MedicalSpecialistPharmacyEtcWithin10MinutesOnFootOrByPublicTransportAndWithin700Meters";
			} break;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_Daycare";
				case 1 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_SecondaryOrVocationalSchool";
				case 2 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_CinemaTheatreOrGallery";
				case 3 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_Bookstore";
				case 4 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_QuarterCenter";
				case 5 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_ParishHall";
				case 6 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_YouthCenter";
				case 7 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_ElderlyCenter";
				case 8 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_FitnessCenter";
				case 9 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_FitnessProgramOpenToExternalUsers";
				case 10 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_Playground";
				case 11 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_GymSportsFieldOrSwimmingPool";
				case 12 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_LocalAmeneties1_ShoppingCenter";
				case 13 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_LocalAmeneties2_Retailers_BakeryButcherDrugstoreEtc";
				case 14 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_LocalAmeneties3_FarmersMarket";
				case 15 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_Gastronomy_RestaurantCafeBakeryEtc";
				case 16 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_OtherServices_BankPostOfficeBarberFitnessCenterWellnessCenter";
				case 17 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_Healthcare1_GeneralPractitioner";
				case 18 : if (no_description != nullptr) *no_description = true; return "BAIUDIHD_Healthcare2_MedicalSpecialistPharmacyEtc";
			} break;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BAIUDCEODNE_UnconventionalOffersPresentedToUsersAndExternals";
				case 1 : if (no_description != nullptr) *no_description = true; return "BAIUDCEODNE_ConstructionalImplementationOrPreparationOfOffers";
			} break;
			// Soc1_1_1::para_t
			case 212 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_1_1_ShoppingCenterRentalAreaCoolingLoad";
			} break;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category3";
				case 1 : if (no_description != nullptr) *no_description = true; return "OTRTOT_Max5PercentDeviationFromDIN_EN_16798_1_Category1and2";
				case 2 : if (no_description != nullptr) *no_description = true; return "OTRTOT_ShoppingCenterRentalAreaCoolingLoadCertification";
				case 3 : if (no_description != nullptr) *no_description = true; return "OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category3";
				case 4 : if (no_description != nullptr) *no_description = true; return "OTRTOT_ShoppingCenterMallStreetMax5PercentDeviationFromDIN_EN_16798_1_Category1and2";
				case 5 : if (no_description != nullptr) *no_description = true; return "OTRTOT_LogisticsAndProductionMeasuresTakenAbove26Degrees";
				case 6 : if (no_description != nullptr) *no_description = true; return "OTRTOT_LogisticsAndProductionLimitationTo30Degrees";
			} break;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RHHP_RelativeHumidityHigherThan30Percent";
				case 1 : if (no_description != nullptr) *no_description = true; return "RHHP_HotelRelativeHumidityLowerThan70Percent";
				case 2 : if (no_description != nullptr) *no_description = true; return "RHHP_ConditionMetFor95PercentOfTime";
			} break;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RHCP_MaxHumidity12GramPerKilogram";
			} break;
			// Soc1_1_3::D_CoolingPeriod
			case 216 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DCP_ObservationOfDIN_EN_ISO_7730_A_A2_KatB";
				case 1 : if (no_description != nullptr) *no_description = true; return "DCP_ShoppingCenterPreventionOfDraught";
			} break;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_CeilingMin16Degrees";
				case 1 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_CeilingMax35Degrees";
				case 2 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_GlassSurfacesMin18Degrees";
				case 3 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_GlassSurfacesMax35Degrees";
				case 4 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_FloorMin19Degrees";
				case 5 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_FloorMax29Degrees";
				case 6 : if (no_description != nullptr) *no_description = true; return "RTAFTCP_LogisticAndProductionMeasuresTakenToPreventRTA";
			} break;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "A2030CARTC_ExceedanceFrequencyEvaluatedBasedOnPrognosticationsDWDTRYFuture";
				case 1 : if (no_description != nullptr) *no_description = true; return "A2030CARTC_ResultsHaveBeenIncludedInPlanningProcess";
			} break;
			// Soc1_1_6::UI_UserInfluence
			case 219 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "UI_PossibilityOfReuse";
				case 1 : if (no_description != nullptr) *no_description = true; return "UI_RoomAirCycleIndividuallyManipulable";
				case 2 : if (no_description != nullptr) *no_description = true; return "UI_RoomTemperatureIndividuallyManipulable";
				case 3 : if (no_description != nullptr) *no_description = true; return "UI_SurveyOnUserSatisfactionAndEnergyEfficiency";
			} break;
			// Soc1_1_Alt::AC_Innovation
			case 220 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AC_AlternativeCertificationForIndicators1to4";
			} break;
			// Soc1_2_1::para_t
			case 221 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_2_TVOC";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_2_Formaldehyde";
				case 2 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_2_TVOCRenterPromise";
				case 3 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_2_FormaldehydeRenterPromise";
			} break;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHTVOCM_TVOCResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHTVOCM_FormaldehydeResultsSubmitted";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHTVOCM_AlternativeCertification";
				case 3 : if (no_description != nullptr) *no_description = true; return "IHTVOCM_ResidentialDegreeOfRentExtensionHigherThan80Percent";
				case 4 : if (no_description != nullptr) *no_description = true; return "IHTVOCM_LP_DeclarationAndVerificationOfProductsForFloors";
				case 5 : if (no_description != nullptr) *no_description = true; return "IHTVOCM_LP_DeclarationAndVerificationOfProductsForAllInteriorSurfaces";
			} break;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHTVOCSCCBCS_OnlyLowEmissionMaterialsUsed";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In50PercentOfSpaces";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHTVOCSCCBCS_RentersHoldUpEnv1_2QS3In80PercentOfSpaces";
			} break;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHTVOCA2030IATMRHC_NonSmokerProtection";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHTVOCA2030IATMRHC_RespirableDustPrevention";
			} break;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHTVOCWWB_WoodworkApplicable";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHTVOCWWB_LimoneneBelowNOW";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHTVOCWWB_AlphaPineneBelowNOW";
			} break;
			// Soc1_2_2::para_t
			case 226 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_2_2_1_a_PercentageOfMechanicalAeration";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_2_2_1_a_ZonalStreamingSimulationResult";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_RatioSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ZonalStreamingSimulation";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat3";
				case 3 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat2";
				case 4 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_MechanicalDIN_EN_16798_1_Kat1";
				case 5 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ManualNoCertification";
				case 6 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ManualObservationOfASR3_6";
				case 7 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ManualObservationOfASR3_6AndSensorMonitoring";
				case 8 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat4";
				case 9 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat3";
				case 10 : if (no_description != nullptr) *no_description = true; return "IHACFOEHAH_ZonalDIN_EN_16798_1_Kat1and2";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHACFSCCBCS_DIN_EN_16798_1_Kat4_CBCSandSCShops";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHACFSCCBCS_DIN_EN_16798_1_Kat3_CBCSandSCShops";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_CBCSandSCShops";
				case 3 : if (no_description != nullptr) *no_description = true; return "IHACFSCCBCS_DIN_EN_16798_1_Kat4_SCMalls";
				case 4 : if (no_description != nullptr) *no_description = true; return "IHACFSCCBCS_DIN_EN_16798_1_Kat3_SCMalls";
				case 5 : if (no_description != nullptr) *no_description = true; return "IHACFSCCBCS_DIN_EN_16798_1_Kat1and2_SCMalls";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHACFR_AerationMeasuresAccordingToLevelsFL";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHACFR_AerationMeasuresAccordingToLevelsRL";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHACFR_AerationMeasuresAccordingToLevelsNL";
			} break;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IHACFLP_NoCertification";
				case 1 : if (no_description != nullptr) *no_description = true; return "IHACFLP_ObservationOfASR3_6";
				case 2 : if (no_description != nullptr) *no_description = true; return "IHACFLP_NeedbasedAeration";
				case 3 : if (no_description != nullptr) *no_description = true; return "IHACFLP_AerationExceedsMinimumRateByAtLeast20Percent";
			} break;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ORSRHcHA_DIN_4109_5_RaisedSoundproofingMet";
			} break;
			// Soc1_3_1::ORSR_Office
			case 232 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ORSRO_ObservationOfVDI_2569_ClassAorBRequirements";
			} break;
			// Soc1_3_1::ORSR_Residential
			case 233 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ORSRR_DIN_4109_5_RequirementsMet";
				case 1 : if (no_description != nullptr) *no_description = true; return "ORSRR_SoundproofingPassClassCOrBetter";
			} break;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "BAMOEHAHcR_ConfirmationThroughMeasuring";
			} break;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PAACRAC_CreationOfPlanningAccompanyingRoomAcousticConcept";
			} break;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RAHHcAEO_ObservationOfDIN_18041ForRoomTypesAAndB";
				case 1 : if (no_description != nullptr) *no_description = true; return "RAHHcAEO_ObservationOfDIN_18041ForInclusiveUse";
				case 2 : if (no_description != nullptr) *no_description = true; return "RAHHcAEO_ObservationOfVDI_2569ClassA";
				case 3 : if (no_description != nullptr) *no_description = true; return "RAHHcAEO_ObservationOfVDI_2569ClassB";
				case 4 : if (no_description != nullptr) *no_description = true; return "RAHHcAEO_MeasuresTakenAndVerified";
			} break;
			// Soc1_3_3::RA_Residential
			case 237 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RAR_RoomAcousticMeasuresTakenForSharedHallwaysAndStairways";
				case 1 : if (no_description != nullptr) *no_description = true; return "RAR_RoomAcousticMeasuresTakenForSharedGroupMealAndLectureRooms";
			} break;
			// Soc1_4_1::para_t
			case 238 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_1ET";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_1D";
				case 2 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_1LitAreaPercentageOfUsableArea";
			} break;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DSOEARHHcP_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "DSOEARHHcP_HotelAlternativeCertification";
			} break;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DSOCSSCCB_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "DSOCSSCCB_ConvenienceStoreEqualDistributionOfCeilingLight";
			} break;
			// Soc1_4_2::para_t
			case 241 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_2UsageLighting";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_2TranslucentCeilingLightPortion";
			} break;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ARULOEALHc_UsageLightingResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "ARULOEALHc_TranslucentCeilingLightPortionResultsSubmitted";
				case 2 : if (no_description != nullptr) *no_description = true; return "ARULOEALHc_AssemblyAreaType1";
				case 3 : if (no_description != nullptr) *no_description = true; return "ARULOEALHc_AssemblyAreaType2";
			} break;
			// Soc1_4_3::para_t
			case 243 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_3_1aPercentageOfOpenFacade";
				case 1 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_3_1aPercentageOfDirectLOSOfShopAreasToOutside";
			} break;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LOSOCSCBSC_QSMedium_DirectOutsideLOSForAllOfficesAnd80PercentOfBreakAndSocialRooms";
				case 1 : if (no_description != nullptr) *no_description = true; return "LOSOCSCBSC_QSLow_CBSC_PercentageOfOpenFacadeResultsSubmitted";
				case 2 : if (no_description != nullptr) *no_description = true; return "LOSOCSCBSC_QSMediumC_BSC_ShopsHaveOutsideLOS";
				case 3 : if (no_description != nullptr) *no_description = true; return "LOSOCSCBSC_QSLOW_CBSC_PercentageOfDirectLOSOfShopAreasToOutsideResultsSubmitted";
				case 4 : if (no_description != nullptr) *no_description = true; return "LOSOCSCBSC_QSLOW_CashierAreasOutsideLOS";
			} break;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_QSLow_OutsideAreasIntervisibility";
				case 1 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_QSMedium_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility";
				case 2 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_QShigh_WorkplaceResidentialAreaHotelRoomCommonRoomIntervisibility";
				case 3 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_RHHc_AlternativeRequirementsMet";
				case 4 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_AssemblyType1";
				case 5 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_AssemblyType2";
				case 6 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_AnyDaylightInCommonAreas";
				case 7 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_QSLow_OutsideAreaIntervisibility";
				case 8 : if (no_description != nullptr) *no_description = true; return "LOSOOEHLARHc_QSLow_OutsideAreaDirectIntervisibility";
			} break;
			// Soc1_4_4::para_t
			case 246 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CurrentValue_soc1_4_4_1DaylightGlareProbability";
			} break;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DGSOEA12Hc_DGPResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "DGSOEA12Hc_AssemblyType1";
				case 2 : if (no_description != nullptr) *no_description = true; return "DGSOEA12Hc_AssemblyType2";
				case 3 : if (no_description != nullptr) *no_description = true; return "DGSOEA12Hc_A2_CombinationOfLightDivertingSystemsAndGlareShields";
				case 4 : if (no_description != nullptr) *no_description = true; return "DGSOEA12Hc_A2_UseOfHighNorthLightDiffusionCeilingLights";
			} break;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DGSCS_ObservationOfASRA3_4Chapter4_2";
			} break;
			// Soc1_4_4::DGS_Logistics
			case 249 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DGSL_UncertifiedGlareShieldSystem";
				case 1 : if (no_description != nullptr) *no_description = true; return "DGSL_Class2GlareShieldSystem";
				case 2 : if (no_description != nullptr) *no_description = true; return "DGSL_Class3OrHigherGlareShieldSystem";
			} break;
			// Soc1_4_4::DGS_Production
			case 250 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "DGSP_CombinationOfLightDivertingSystemsAndGlareShields";
				case 1 : if (no_description != nullptr) *no_description = true; return "DGSP_UseOfHighNorthLightDiffusionCeilingLights";
			} break;
			// Soc1_4_5::AL_LightingConcept
			case 251 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ALLC_CreationOfLightingConcept";
			} break;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ALIPCOR_DIN_EN_12464_1_IlluminationRequirementsMet";
				case 1 : if (no_description != nullptr) *no_description = true; return "ALIPCOR_AtLeastTwoOptimisationMeasuresTaken";
				case 2 : if (no_description != nullptr) *no_description = true; return "ALIPCOR_AdditionalOptimisationMeasuresTaken";
			} break;
			// Soc1_4_6::SED_Residential
			case 253 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SEDR_1_5HoursExposureOfAtLeastOneRoomOfResidentialUnit";
				case 1 : if (no_description != nullptr) *no_description = true; return "SEDR_2HoursExposureOfAtLeastOneRoomOfResidentialUnit";
				case 2 : if (no_description != nullptr) *no_description = true; return "SEDR_3HoursExposureOfAtLeastOneRoomOfResidentialUnit";
			} break;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SEDHHC_1_5HoursExposureIn100PercentOfUnitsOrRooms";
				case 1 : if (no_description != nullptr) *no_description = true; return "SEDHHC_2HoursExposureIn50PercentOfUnitsOrRooms";
				case 2 : if (no_description != nullptr) *no_description = true; return "SEDHHC_2HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent";
				case 3 : if (no_description != nullptr) *no_description = true; return "SEDHHC_3HoursExposureIn60PercentOfUnitsOrRoomsAnd1_5HoursExposureInRemaining40Percent";
			} break;
			// Soc1_6_1::para_t
			case 255 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AlternativeInnovativeCommunicationConstellations";
			} break;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CSOCZMU_DifferentCommunicationZones";
				case 1 : if (no_description != nullptr) *no_description = true; return "CSOCZMU_CommunicationSupportingRoomDesign";
				case 2 : if (no_description != nullptr) *no_description = true; return "CSOCZMU_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_2::para_t
			case 257 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Soc1_6_2_1AlternativeInnovativeSolutions";
				case 1 : if (no_description != nullptr) *no_description = true; return "Soc1_6_2_2AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AOUAOS_AdditionalOffersMultifunctionRoomsCommonRooms";
				case 1 : if (no_description != nullptr) *no_description = true; return "AOUAOS_CSCBSC_LockersChangingRooms";
				case 2 : if (no_description != nullptr) *no_description = true; return "AOUAOS_Residential_CommonRoomsAvailableToEveryone";
				case 3 : if (no_description != nullptr) *no_description = true; return "AOUAOS_Residential_LaundryAndDryingRoomsFunctionAsCommonRooms_PartialWaivingOfLaundryMachineConnectionsInResidentialUnits";
				case 4 : if (no_description != nullptr) *no_description = true; return "AOUAOS_Hc_AdditionalOffersAvailableToEveryone";
				case 5 : if (no_description != nullptr) *no_description = true; return "AOUAOS_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AOUOI_Signage";
				case 1 : if (no_description != nullptr) *no_description = true; return "AOUOI_InformationDesk";
				case 2 : if (no_description != nullptr) *no_description = true; return "AOUOI_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_3::para_t
			case 260 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Soc1_6_3_1AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_Daycare";
				case 1 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_BabyChangeAndSeparateBreastFeedingRooms";
				case 2 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_Playground";
				case 3 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_ElderlyCommonRoomsPlayrooms";
				case 4 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_FamilyFriendlyParking";
				case 5 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithBabyChange";
				case 6 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithCrib";
				case 7 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithKitchenette";
				case 8 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_Hotel_5PercentOfRoomsOutfittedWithDarkeningBlind";
				case 9 : if (no_description != nullptr) *no_description = true; return "FCEFOSO_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_4::para_t
			case 262 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Soc1_6_4_1AlternativeInnovativeSolutions";
			} break;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QSIAA_WideningsGalleriesNichesStairwellsOfSufficientWidthAndAirSpaceForCrossFloorCommunication";
				case 1 : if (no_description != nullptr) *no_description = true; return "QSIAA_DaylightAvailabilityInAllotmentAreas";
				case 2 : if (no_description != nullptr) *no_description = true; return "QSIAA_DoorwayOpeningsToBalconiesRoofTerracesAtria";
				case 3 : if (no_description != nullptr) *no_description = true; return "QSIAA_AllotmentAreasFeatureHeightenedThermalAcousticOrSoundproofingRequirementsEnablingFlexibleUse";
				case 4 : if (no_description != nullptr) *no_description = true; return "QSIAA_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::para_t
			case 264 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Soc1_6_5_3AlternativeInnovativeSolutions";
				case 1 : if (no_description != nullptr) *no_description = true; return "Soc1_6_5_4AlternativeInnovativePoints";
			} break;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QSDCOA_DesignConceptFulfillsUserRequirementsAndFeaturesDifferentFunctions";
				case 1 : if (no_description != nullptr) *no_description = true; return "QSDCOA_DesignConsidersMaterialQuality";
				case 2 : if (no_description != nullptr) *no_description = true; return "QSDCOA_DesignConsidersEnvironmentFriendlyAndSociallyAcceptableLighting";
				case 3 : if (no_description != nullptr) *no_description = true; return "QSDCOA_DesignConsidersIntuitiveOrientation";
				case 4 : if (no_description != nullptr) *no_description = true; return "QSDCOA_DesignAvoidsPlacesOfAnxiety";
				case 5 : if (no_description != nullptr) *no_description = true; return "QSDCOA_DesignConsidersIntegrationAndGreeningOfTechnicalFacilities";
				case 6 : if (no_description != nullptr) *no_description = true; return "QSDCOA_AlternativeCertification_DesignGuidelinesFeatureIndividualPreferencesOfResidents";
				case 7 : if (no_description != nullptr) *no_description = true; return "QSDCOA_Healthcare_CommonAreasNotExposedToNoiseMalodorOrSimilarConstrictions";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QSOCA_MoreThan10PercentOfRooftopAtLeast5m2";
				case 1 : if (no_description != nullptr) *no_description = true; return "QSOCA_CSCBSC_MoreThan1PercentOfRooftop";
				case 2 : if (no_description != nullptr) *no_description = true; return "QSOCA_BalconiesLoggiasWinterGardenOfAtLeast3m2PerUnit";
				case 3 : if (no_description != nullptr) *no_description = true; return "QSOCA_MoreThan25PercentOfOutdoorAreaAtLeast30m2_AccordingToDIN_277";
				case 4 : if (no_description != nullptr) *no_description = true; return "QSOCA_Healthcare_BalconiesLoggiasWinterGardenAccessbileForMostUsers";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QSOCASU_AllotmentAndNetworkingFunction";
				case 1 : if (no_description != nullptr) *no_description = true; return "QSOCASU_AccessibilityToPublic";
				case 2 : if (no_description != nullptr) *no_description = true; return "QSOCASU_MeetupAndCommunicationFunction";
				case 3 : if (no_description != nullptr) *no_description = true; return "QSOCASU_ExerciseAndPlayFunction";
				case 4 : if (no_description != nullptr) *no_description = true; return "QSOCASU_WorkAndConcentrationFunction";
				case 5 : if (no_description != nullptr) *no_description = true; return "QSOCASU_RestAndRecuperationFunction";
				case 6 : if (no_description != nullptr) *no_description = true; return "QSOCASU_SocialControlOfOutdoorAreasThroughBuildingExteriorRelation";
				case 7 : if (no_description != nullptr) *no_description = true; return "QSOCASU_EnvironmentFriendlyAndSociallyAcceptableLighting";
				case 8 : if (no_description != nullptr) *no_description = true; return "QSOCASU_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QSDCOAC_SolarisationOnDec21AtLeast1Hour";
				case 1 : if (no_description != nullptr) *no_description = true; return "QSDCOAC_SolarisationOnDec21AtLeast3Hours";
				case 2 : if (no_description != nullptr) *no_description = true; return "QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn10PercentOrMore";
				case 3 : if (no_description != nullptr) *no_description = true; return "QSDCOAC_SummerSunblindThroughTreesShadingOrBuildingsOn30PercentOrMore";
				case 4 : if (no_description != nullptr) *no_description = true; return "QSDCOAC_WindShieldNoNegativeEffectsOnCommonAreasOrPreventativeMeasures";
				case 5 : if (no_description != nullptr) *no_description = true; return "QSDCOAC_InnovationRoomAlternativeCertification";
			} break;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QSA2030_ClimateProtectionFactorOfSurfaceStructures";
				case 1 : if (no_description != nullptr) *no_description = true; return "QSA2030_ClimateProtectionProtectionOptimisationOfOutdoorAreas";
			} break;
			// Soc2_1_1::para_t
			case 270 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Soc2_1_1Qualitystage";
			} break;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AQST_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "AQST_Residential_StudentHostelBoardingHouses";
				case 2 : if (no_description != nullptr) *no_description = true; return "AQST_Residential_NursingHomesHospicesDisabledElderly";
			} break;
			// Socioculture::para_weights
			case 272 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PW_Soc1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PW_Soc1_2";
				case 2 : if (no_description != nullptr) *no_description = true; return "PW_Soc1_3";
				case 3 : if (no_description != nullptr) *no_description = true; return "PW_Soc1_4";
				case 4 : if (no_description != nullptr) *no_description = true; return "PW_Soc1_6";
				case 5 : if (no_description != nullptr) *no_description = true; return "PW_Soc2_1";
			} break;
			// Socioculture::para_goals
			case 273 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PG_Soc1_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "PG_Soc1_2";
				case 2 : if (no_description != nullptr) *no_description = true; return "PG_Soc1_3";
				case 3 : if (no_description != nullptr) *no_description = true; return "PG_Soc1_4";
				case 4 : if (no_description != nullptr) *no_description = true; return "PG_Soc1_6";
				case 5 : if (no_description != nullptr) *no_description = true; return "PG_Soc2_1";
			} break;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PABEPFE_PotentialOfSolarEnergy";
				case 1 : if (no_description != nullptr) *no_description = true; return "PABEPFE_PotentialOfGreening";
				case 2 : if (no_description != nullptr) *no_description = true; return "PABEPFE_AnalysisOfDifferentVariationsFocusedOnSustainabilityThroughoutLifeCycle";
				case 3 : if (no_description != nullptr) *no_description = true; return "PABEPFE_UseOfSustainableResourcesForInsulationAndCladding";
				case 4 : if (no_description != nullptr) *no_description = true; return "PABEPFE_PossibilityOfNondestructiveReplacementOfParts";
				case 5 : if (no_description != nullptr) *no_description = true; return "PABEPFE_AnalysisOfDifferentVariationsFocusedOnHeatLossOverBuildingEnvelope";
			} break;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TOESEP_NominalRoomTemperature19Degrees";
				case 1 : if (no_description != nullptr) *no_description = true; return "TOESEP_19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_18";
				case 2 : if (no_description != nullptr) *no_description = true; return "TOESEP_19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_0";
				case 3 : if (no_description != nullptr) *no_description = true; return "TOESEP_19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan1_6";
				case 4 : if (no_description != nullptr) *no_description = true; return "TOESEP_NominalRoomTemperatureBetween12And19Degrees";
				case 5 : if (no_description != nullptr) *no_description = true; return "TOESEP_12to19Degrees_OpaqueExteriorBuildingElementsHTCLessThan0_24";
				case 6 : if (no_description != nullptr) *no_description = true; return "TOESEP_12to19Degrees_TransparentExteriorBuildingElementsAndFrontsHTCLessThan1_3";
				case 7 : if (no_description != nullptr) *no_description = true; return "TOESEP_12to19Degrees_OtherTransparentElementsLikeGlassRoofsLightBandsLightDomesHTCLessThan2_0";
				case 8 : if (no_description != nullptr) *no_description = true; return "TOESEP_Residential_TransmissionOverHullSurfaceComparedToReferenceBuildingLessThan55Percent";
			} break;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "TOESTBS_EvaluationImpossible";
				case 1 : if (no_description != nullptr) *no_description = true; return "TOESTBS_SurchargeLessThan0_05";
				case 2 : if (no_description != nullptr) *no_description = true; return "TOESTBS_SurchargeLessThan0_01";
			} break;
			// Tec1_3_3::para_t
			case 277 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Tec1_3_3AirExchangeRateThroughBuildingEnvelope";
				case 1 : if (no_description != nullptr) *no_description = true; return "Tec1_3_3AirExchangeRateRelativeToEnvelopeSurface		[-]		// ToDo Einheit";
			} break;
			// Tec1_3_3::ABE_Measuring
			case 278 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ABEM_BuildingAirVolumeGreaterThan1500sqm";
				case 1 : if (no_description != nullptr) *no_description = true; return "ABEM_BuildingAirVolumeLessThan1500sqm";
				case 2 : if (no_description != nullptr) *no_description = true; return "ABEM_ResultsSubmitted";
			} break;
			// Tec1_3_4::para_t
			case 279 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Tec1_3_4UntercuttingOfLegalRequirements";
			} break;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "HISVV_ExaminationOfDifferentVariations";
				case 1 : if (no_description != nullptr) *no_description = true; return "HISVV_ExaminationOfNonCommonRooms";
				case 2 : if (no_description != nullptr) *no_description = true; return "HISVV_ExaminationOfBuildingWithLocalClimateDataAndImplementationOfResultsDuringPlanning";
				case 3 : if (no_description != nullptr) *no_description = true; return "HISVV_UndercuttingLegalMinimumRequirementsByAtLeast20PercentResultsSubmitted";
			} break;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "QAMQC_BlowerDoorTest";
				case 1 : if (no_description != nullptr) *no_description = true; return "QAMQC_BuildingThermographyDuringBuildingPhase";
				case 2 : if (no_description != nullptr) *no_description = true; return "QAMQC_OtherRelevantMeasurements";
			} break;
			// Tec1_4_1::PS_Planning
			case 282 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PSP_HighCompactness";
				case 1 : if (no_description != nullptr) *no_description = true; return "PSP_BalancedWindowAreaRatioUnderConsiderationOfShading";
				case 2 : if (no_description != nullptr) *no_description = true; return "PSP_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer";
				case 3 : if (no_description != nullptr) *no_description = true; return "PSP_AsManyNaturallyLightedRoomsAsPossible";
				case 4 : if (no_description != nullptr) *no_description = true; return "PSP_UseOfHighMassElementsForHeatStorage";
				case 5 : if (no_description != nullptr) *no_description = true; return "PSP_PassiveCooling";
				case 6 : if (no_description != nullptr) *no_description = true; return "PSP_EffectiveNaturalAeration";
			} break;
			// Tec1_4_1::PS_Implementation
			case 283 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PSI_HighCompactness";
				case 1 : if (no_description != nullptr) *no_description = true; return "PSI_BalancedWindowAreaRatioUnderConsiderationOfShading";
				case 2 : if (no_description != nullptr) *no_description = true; return "PSI_ConstructionalSunblindToPreventDirectSunlightOnWindowsDuringSummer";
				case 3 : if (no_description != nullptr) *no_description = true; return "PSI_AsManyNaturallyLightedRoomsAsPossible";
				case 4 : if (no_description != nullptr) *no_description = true; return "PSI_UseOfHighMassElementsForHeatStorage";
				case 5 : if (no_description != nullptr) *no_description = true; return "PSI_PassiveCooling";
				case 6 : if (no_description != nullptr) *no_description = true; return "PSI_EffectiveNaturalAeration";
			} break;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AAOTIREW_AverageTemperatureOf50DegreesOrMore";
				case 1 : if (no_description != nullptr) *no_description = true; return "AAOTIREW_AverageTemperatureBetween35and50Degrees";
				case 2 : if (no_description != nullptr) *no_description = true; return "AAOTIREW_AverageTemperatureOf35DegreesOrLess";
				case 3 : if (no_description != nullptr) *no_description = true; return "AAOTIREW_NoHeatingSystemInBuilding";
				case 4 : if (no_description != nullptr) *no_description = true; return "AAOTIREW_100PercentOfWarmthDemandCoveredByRegenerativeEnergy";
			} break;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "AAOTIREC_AverageTemperatureOf14DegreesOrLess";
				case 1 : if (no_description != nullptr) *no_description = true; return "AAOTIREC_AverageTemperatureBetween14and19Degrees";
				case 2 : if (no_description != nullptr) *no_description = true; return "AAOTIREC_AverageTemperatureOf19DegreesOrMore";
				case 3 : if (no_description != nullptr) *no_description = true; return "AAOTIREC_NoCoolingSystemInBuilding";
				case 4 : if (no_description != nullptr) *no_description = true; return "AAOTIREC_100PercentOfCoolingDemandCoveredByRegenerativeEnergy";
			} break;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ABSSEC_GenerallyGoodAccessibilityOfAllSystemComponentsForReplacementAndRetrofitting";
				case 1 : if (no_description != nullptr) *no_description = true; return "ABSSEC_SufficientNumberAndSizeOfOpeningsDoorsAndHallways";
				case 2 : if (no_description != nullptr) *no_description = true; return "ABSSEC_TransportAndReplacementOfComponentsPossibleWithoutConstructionalMeasures";
			} break;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ABSDTA_VerticalDuctsAndTracesOfAllSubsectionsAccessible";
				case 1 : if (no_description != nullptr) *no_description = true; return "ABSDTA_PossibilityOfRetrofittingWithoutMajorDisturbanceToBuildingOperation";
			} break;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ISSU_PlanningAndImplementationAccordingToDIN_EN_ISO_16484_1";
				case 1 : if (no_description != nullptr) *no_description = true; return "ISSU_OpenAndStandardizedProtocolsInExistingNetworks";
			} break;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ISIFSS_Sunblind";
				case 1 : if (no_description != nullptr) *no_description = true; return "ISIFSS_Lighting";
				case 2 : if (no_description != nullptr) *no_description = true; return "ISIFSS_Heating";
				case 3 : if (no_description != nullptr) *no_description = true; return "ISIFSS_Aeration";
				case 4 : if (no_description != nullptr) *no_description = true; return "ISIFSS_Cooling";
				case 5 : if (no_description != nullptr) *no_description = true; return "ISIFSS_EnergyManagement";
				case 6 : if (no_description != nullptr) *no_description = true; return "ISIFSS_PresenceDetection";
				case 7 : if (no_description != nullptr) *no_description = true; return "ISIFSS_Lifts";
			} break;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ISPITSMQDS_AnalysisOfExistingEnergyPotentialAndPossibleNetworkingWithExistingSurroundingEnergyInfrastructure";
				case 1 : if (no_description != nullptr) *no_description = true; return "ISPITSMQDS_CreationOfQuarterRelatedEnergyBalancesForHeatingCoolingAndElectricityEcologicalComparisonOfTheEmissionsOfAtLeast3PeripheralAndOrCentralHeatSupplyVariants";
				case 2 : if (no_description != nullptr) *no_description = true; return "ISPITSMQDS_EconomicalAssessmentOfInvestmentsAndOperatingCostsForAtLeast3SupplyVariants";
				case 3 : if (no_description != nullptr) *no_description = true; return "ISPITSMQDS_AnalysisOfAppropriationOfRegenerativelyProducedEnergyForQuarterAndSurroudingsUnterInclusionOfPossibleConsumers";
			} break;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ISIITSMQDS_ImplementationWithTheGoalOfSynergisticUseInRelationToQuarterAndDirectSurroundings";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ISIEIQDSQS_BuildingUsesEnergyFromNearbyQuartersOrDirectSurroundingsToFulfillEnergyDemand";
				case 1 : if (no_description != nullptr) *no_description = true; return "ISIEIQDSQS_BuildingProvidesGeneratedRegenerativeEnergyToNearbyQuartersAndDirectSurroundings";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "ISIITSMQNES_BuildingProvidesRelevantStorageCapacity";
				case 1 : if (no_description != nullptr) *no_description = true; return "ISIITSMQNES_BuildingUsesExistingIntegratedEnergyAndLoadManagement";
			} break;
			// Tec1_4_5::URE_EnergySources
			case 294 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "UREES_PortionOfEnergyFromRenewableSourcesAtLeast85Percent";
				case 1 : if (no_description != nullptr) *no_description = true; return "UREES_PortionOfEnergyFromRenewableSourcesAtLeast95Percent";
			} break;
			// Tec1_4_5::URE_Production
			case 295 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "UREP_AtLeast60PercentOfSuitableRoofAreaUsedForSolarEnergyProduction";
				case 1 : if (no_description != nullptr) *no_description = true; return "UREP_AtLeast60PercentOfSuitableParkingAreaUsedForSolarEnergyProduction";
				case 2 : if (no_description != nullptr) *no_description = true; return "UREP_Residential_MinimumPowerOf0_06kWPeakPerSQMOfPlot";
				case 3 : if (no_description != nullptr) *no_description = true; return "UREP_AtLeast80PercentOfSuitableRoofAreaUsedForSolarEnergyProduction";
				case 4 : if (no_description != nullptr) *no_description = true; return "UREP_AtLeast80PercentOfSuitableParkingAreaUsedForSolarEnergyProduction";
				case 5 : if (no_description != nullptr) *no_description = true; return "UREP_Residential_MinimumPowerOf0_08kWPeakPerSQMOfPlot";
			} break;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCPID161_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SSAPPDA_CircularConstructionPotentialsOfSiteAndRegionResourcesHasBeenAnalysed";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SSAPPDCEBSPU_StockPreserved";
				case 1 : if (no_description != nullptr) *no_description = true; return "SSAPPDCEBSPU_StockExpanded";
				case 2 : if (no_description != nullptr) *no_description = true; return "SSAPPDCEBSPU_StockElementsPutToUse";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SSAPPDDJ_JustificationProvided";
				case 1 : if (no_description != nullptr) *no_description = true; return "SSAPPDDJ_InventoryOfPartsMaterialFlowBalanceStockAnalysisTaken";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SSAPPDDE_ProactiveSearchForBuyersOrAcceptorsOfPartsAndProductsDuringDemolition";
				case 1 : if (no_description != nullptr) *no_description = true; return "SSAPPDDE_InventoryTakenForMassesAndTransportDistances";
				case 2 : if (no_description != nullptr) *no_description = true; return "SSAPPDDE_MeasuresTakenToOptimiseReuseAndDisposal";
				case 3 : if (no_description != nullptr) *no_description = true; return "SSAPPDDE_RecommendedOrOtherSuitableMeasuresAgainstHazardousMaterialsTaken";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SSAPPDDAC_DGNBDemolitionCertificationFollowed";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "SSAPPDCERS_MaterialsOrElementsLeftFromDemolitionReusedInProject";
			} break;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCPID162_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCCPGFD_PlanningWithCircularGoal";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCCPGFD_Alt_PlanIncludesPreexistingRecyclableMaterials";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCCPPRCDCEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCCPPRCDCEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCCPPRCDCAEP_CreationAndEvaluationOfVariantsOfAtLeast4Topics";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCCPPRCDCAEP_Alt_UseOfToolsForCreationOfCircularityOptimisationBalancesAndIndices";
				case 2 : if (no_description != nullptr) *no_description = true; return "CCCPPRCDCAEP_Alt_GenerationOfABuildingResourcePass";
				case 3 : if (no_description != nullptr) *no_description = true; return "CCCPPRCDCAEP_ParallelEvaluationOfClimateInfluenceAndCosts";
			} break;
			// Tec1_6_3::para_t
			case 307 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructions";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayering";
			} break;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCPID163_DemolitionOrPartialDemolition";
			} break;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDDCBPBP_ReducedBuildingPass";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDDCBPBP_CompleteBuildingPass";
			} break;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDERCPBL_ModerateGoalQuotaReachedForAllProperties";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDERCPBL_HighGoalQuotaReachedForAtLeast2Properties";
			} break;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDUCPCEL_UseOfProductsOfQS4";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDUCPCEL_UseOfProductsOfQS3";
				case 2 : if (no_description != nullptr) *no_description = true; return "CCEDUCPCEL_UseOfProductsOfQS2";
				case 3 : if (no_description != nullptr) *no_description = true; return "CCEDUCPCEL_UseOfProductsOfQS1";
				case 4 : if (no_description != nullptr) *no_description = true; return "CCEDUCPCEL_RequirementsOfSimplifiedMethodFulfilled";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDCERMACAMMCI_UseOfRecycledMaterials";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDCERMACAMMCI_NumberOfConstructionsUsingMaterialAppropriateConstructionsResultsSubmitted";
				case 2 : if (no_description != nullptr) *no_description = true; return "CCEDCERMACAMMCI_NumberOfConstructionsAvoidingMaterialMixingOrLayeringResultsSubmitted";
				case 3 : if (no_description != nullptr) *no_description = true; return "CCEDCERMACAMMCI_CircularAspectsImplementedInConstructiveIntegrations";
			} break;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDRRDI_InstructionsIncludeReuseRebuildingAndDemolition";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDRRDI_InstructionsIncludeRebuildingAndDemolition";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "CCEDCECBACE_MoreThan90PercentOfPartsOriginateFromCircularEconomy";
				case 1 : if (no_description != nullptr) *no_description = true; return "CCEDCECBACE_MoreThan90PercentOfBuildingMassSuitedForReuseInCircularEconomy";
				case 2 : if (no_description != nullptr) *no_description = true; return "CCEDCECBACE_AggregatedCircularyIndexEvaluationDocumentedInBuildingPassAndRatedGoodOrAbove";
			} break;
			// Tec3_1_1::MI_MobilityConcept
			case 315 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "MIMC_ConceptIncludesGoalsForSustainableMobility";
				case 1 : if (no_description != nullptr) *no_description = true; return "MIMC_ConceptIncludesFutureTrafficDemands";
			} break;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IPI_TransparentSafeAndBarrierFreeRoutingVisibleAndComprehensiveSignage";
				case 1 : if (no_description != nullptr) *no_description = true; return "IPI_DesignatedParkingSpotsForMobilityAidsLikeWalkersOrStrollers";
			} break;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IBI_AtLeast80PerceptOfBicycleParkingSpotsAreClearlyRelatedToTheBuildingNearTheEntranceAccessibleAndHaveProtectionAgainstTheft";
				case 1 : if (no_description != nullptr) *no_description = true; return "IBI_Residential100PercentAllOthers80PercentOfParkingSpotsAreEquippedWithWeatherProtection";
				case 2 : if (no_description != nullptr) *no_description = true; return "IBI_SufficientNumberOfParkingSpotsForCargoBikesWithTheftProtection";
			} break;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IMIT_ParkingSpacesReducedAccordingToRegulations";
				case 1 : if (no_description != nullptr) *no_description = true; return "IMIT_ReducedParkingDemandRedirectedToMobilityHubThatFeaturesFurtherReductionsOfTransportationNeeds";
				case 2 : if (no_description != nullptr) *no_description = true; return "IMIT_ParkingSpacesOnSiteFulfillOrganisationalAndConstructionalRequirementsForCarsharing";
				case 3 : if (no_description != nullptr) *no_description = true; return "IMIT_AtLeast80PercentOfParkingSpacesHaveNoDesignatedSpecificOccupant";
				case 4 : if (no_description != nullptr) *no_description = true; return "IMIT_Alternative_MobilityConceptForgoesParkingSpacesWithTheExceptionOfDisabledParkingAndCarsharingSpaces";
			} break;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IA2030MMC_MobilityConceptIncludesMobilityManagementConcept";
			} break;
			// Tec3_1_3::para_t
			case 320 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Tec3_1_3_1IAFSBTEB_NumberOfRequiredBicycleParkingSpots";
				case 1 : if (no_description != nullptr) *no_description = true; return "Tec3_1_3_1IAFSBTEB_NumberOfBicycleParkingSpotsEquippedWithLoadingDock";
				case 2 : if (no_description != nullptr) *no_description = true; return "Tec3_1_3_2IAFSMIT_PercentageOfParkingsSpotsOfPermanentelyDesignatedOccupantsOrResidentsEquippedWithLoadingDock";
				case 3 : if (no_description != nullptr) *no_description = true; return "Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsEquippedWithLoadingDock";
				case 4 : if (no_description != nullptr) *no_description = true; return "Tec3_1_3_2IAFSMIT_TotalNumberOfParkingsSpotsEquippedWithLoadingDock";
				case 5 : if (no_description != nullptr) *no_description = true; return "Tec3_1_3_2IAFSMIT_PercentageOfOtherParkingsSpotsPreparedToBeEquippedWithLoadingDock";
			} break;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IAFSBTEB_ResultsSubmitted";
			} break;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IAFSMIT_ResultsSubmitted";
			} break;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IAFSILTS_IntegrationIntoBuildingEnergyManagement";
				case 1 : if (no_description != nullptr) *no_description = true; return "IAFSILTS_IntegrationIntoLoadingManagementNetwork";
			} break;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "IAFSA2030CPG_VehicleToGrid_SetupForBidirectionalLoadingAndUnloadingOfElectricVehicles";
			} break;
			// Tec3_1_4::para_t
			case 325 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "Tec3_1_4NumberOfIndividualNonOverlappingMobilitySharingOffers";
			} break;
			// Tec3_1_4::RS_MobilitySharing
			case 326 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "RSMS_ResultsSubmitted";
				case 1 : if (no_description != nullptr) *no_description = true; return "RSMS_Alt_BuildingAndOccupantsArePartOfAQuarterMobilityConceptIncludingOrganisationAndSupportOfSharingsystems";
			} break;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "OCBGO_SufficientAvailabilityOfShowers";
				case 1 : if (no_description != nullptr) *no_description = true; return "OCBGO_SufficientAvailabilityOfChangingRoomsAndDryingRoomsForBikeWear";
				case 2 : if (no_description != nullptr) *no_description = true; return "OCBGO_SufficientAvailabilityOfMaintenanceFacilitiesForBikes";
				case 3 : if (no_description != nullptr) *no_description = true; return "OCBGO_Residential_ParkingSpacesForBikeTrailers";
			} break;
			// Technology::para_weights
			case 328 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PW_Tec1_3";
				case 1 : if (no_description != nullptr) *no_description = true; return "PW_Tec1_4";
				case 2 : if (no_description != nullptr) *no_description = true; return "PW_Tec1_6";
				case 3 : if (no_description != nullptr) *no_description = true; return "PW_Tec3_1";
			} break;
			// Technology::para_goals
			case 329 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "PG_Tec1_3";
				case 1 : if (no_description != nullptr) *no_description = true; return "PG_Tec1_4";
				case 2 : if (no_description != nullptr) *no_description = true; return "PG_Tec1_6";
				case 3 : if (no_description != nullptr) *no_description = true; return "PG_Tec3_1";
			} break;
			// Utilities::UsageType
			case 330 :
			switch (t) {
				case 0 : if (no_description != nullptr) *no_description = true; return "offices";
				case 1 : if (no_description != nullptr) *no_description = true; return "education";
				case 2 : if (no_description != nullptr) *no_description = true; return "residential";
				case 3 : if (no_description != nullptr) *no_description = true; return "hotel";
				case 4 : if (no_description != nullptr) *no_description = true; return "convenienceStore";
				case 5 : if (no_description != nullptr) *no_description = true; return "shoppingCenter";
				case 6 : if (no_description != nullptr) *no_description = true; return "commercialBuilding";
				case 7 : if (no_description != nullptr) *no_description = true; return "logistics";
				case 8 : if (no_description != nullptr) *no_description = true; return "production";
				case 9 : if (no_description != nullptr) *no_description = true; return "assembly";
				case 10 : if (no_description != nullptr) *no_description = true; return "healthcare";
			} break;
		} // switch
		throw IBK::Exception(IBK::FormatString("Cannot determine description for enumeration type '%1' and index '%2'.")
			.arg(enumtype).arg(t), "[KeywordList::Description]");
	}

	const char * KeywordList::Unit(const char * const enumtype, int t) {
		switch (enum2index(enumtype)) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Eco1_1_2::para_t
			case 3 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Eco1_1_3::para_t
			case 6 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Eco1_1_3::BRLCC_Calculation
			case 7 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
			} break;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Eco2_4_3::para_t
			case 13 :
			switch (t) {
				case 0 : return "---";
			} break;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_4_4::para_t
			case 16 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
			} break;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_4_7::A2030_Expandability
			case 23 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Eco2_7_3::PPBIM_Preparation
			case 41 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Eco2_7_3::PPBIM_Creation
			case 42 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 :
			switch (t) {
				case 0 : return "";
			} break;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 :
			switch (t) {
				case 0 : return "";
			} break;
			// Economy::para_weights
			case 50 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
			} break;
			// Economy::para_goals
			case 51 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
			} break;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_2::para_t
			case 59 :
			switch (t) {
				case 0 : return "kg pro m² und Jahr";
				case 1 : return "kg pro m² und Jahr";
				case 2 : return "kg pro m² und Jahr";
				case 3 : return "kg pro m² und Jahr";
			} break;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_3::para_t
			case 66 :
			switch (t) {
				case 0 : return "kWh pro m² und Jahr";
				case 1 : return "kWh pro m² und Jahr";
				case 2 : return "troposphärisches Ozon pro m² und Jahr";
				case 3 : return "troposphärisches Ozon pro m² und Jahr";
				case 4 : return "Versauerungspotenzial Boden&Wasser pro m² und Jahr";
				case 5 : return "Versauerungspotenzial Boden&Wasser pro m² und Jahr";
				case 6 : return "Eutrophierungspotenzial pro m² und Jahr";
				case 7 : return "Eutrophierungspotenzial pro m² und Jahr";
				case 8 : return "m3 Frischwasser pro m² und Jahr";
				case 9 : return "m3 Frischwasser pro m² und Jahr";
			} break;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_2_1::para_t
			case 69 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
			} break;
			// Env1_2_1::EFM_A
			case 70 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Env1_2_1::EFM_Agenda2030
			case 73 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_3_2::para_t
			case 78 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_2_2::para_t
			case 85 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
			} break;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_2_5::para_t
			case 89 :
			switch (t) {
				case 0 : return "---";
				case 1 : return "---";
				case 2 : return "---";
			} break;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Env2_3_2::para_t
			case 93 :
			switch (t) {
				case 0 : return "---";
			} break;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_2::para_t
			case 99 :
			switch (t) {
				case 0 : return "---";
				case 1 : return "---";
				case 2 : return "-";
			} break;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_3::para_t
			case 105 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 :
			switch (t) {
				case 0 : return "";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 :
			switch (t) {
				case 0 : return "";
			} break;
			// Environment::para_weights
			case 116 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Environment::para_goals
			case 117 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// KeywordList::MyParameters
			case 118 :
			switch (t) {
				case 0 : return "C";
				case 1 : return "kg";
			} break;
			// Pro1_1_1::RP_Basis
			case 119 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_1_1::RP_RP
			case 120 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro1_1_2::A2030_Participation
			case 122 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro1_6_3::HAA_Recognition
			case 137 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_1_1::NRCS_Concept
			case 138 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_2::DRCS_Concept
			case 141 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_3::SGPCS_Concept
			case 144 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_4::WRCS_Concept
			case 147 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCWU_Concept
			case 155 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCEU_Concept
			case 159 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_1_7::M_Prevention
			case 162 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_3_1::TM_PlanningPhase
			case 163 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_3_3::TrialOperation
			case 165 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_3_6::OperationStartUpManagement
			case 168 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_3_7::BuildingPerformance
			case 169 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_5_1::FM_Check
			case 170 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 :
			switch (t) {
				case 0 : return "";
			} break;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_5_5::SIS_Implementation
			case 174 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Pro2_5_6::OCP_Extended
			case 176 :
			switch (t) {
				case 0 : return "";
			} break;
			// Process::para_weights
			case 177 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Process::para_goals
			case 178 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Site::para_weights
			case 179 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
			} break;
			// Site::para_goals
			case 180 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
			} break;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_1_1::CR_Screening
			case 182 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_1_1::CR_DataBasis
			case 186 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Site1_1_1::CR_ResultApplication
			case 187 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_1_3::EEI_AirQuality
			case 190 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Site1_1_3::EEI_Radon
			case 191 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Site1_3_1::MIT_Surroundings
			case 192 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_3_2::PT_Stations
			case 194 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_3_2::PT_Intervals
			case 196 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_3_2::PT_RelationToBuilding
			case 197 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_3_3::BT_Connection
			case 199 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_3_3::BT_RelationToBuilding
			case 200 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_3_4::FT_SignageSystems
			case 203 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_3_5::AS_Within350Meters
			case 204 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 :
			switch (t) {
				case 0 : return "";
			} break;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
				case 9 : return "";
				case 10 : return "";
				case 11 : return "";
			} break;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
			} break;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
				case 9 : return "";
				case 10 : return "";
				case 11 : return "";
				case 12 : return "";
				case 13 : return "";
				case 14 : return "";
				case 15 : return "";
				case 16 : return "";
				case 17 : return "";
				case 18 : return "";
			} break;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_1_1::para_t
			case 212 :
			switch (t) {
				case 0 : return "W/m2";
			} break;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
			} break;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_1_3::D_CoolingPeriod
			case 216 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
			} break;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_1_6::UI_UserInfluence
			case 219 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Soc1_1_Alt::AC_Innovation
			case 220 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_2_1::para_t
			case 221 :
			switch (t) {
				case 0 : return "kg/m3";
				case 1 : return "kg/m3";
				case 2 : return "kg/m3";
				case 3 : return "kg/m3";
			} break;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_2_2::para_t
			case 226 :
			switch (t) {
				case 0 : return "---";
				case 1 : return "-";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
				case 9 : return "";
				case 10 : return "";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_3_1::ORSR_Office
			case 232 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_3_1::ORSR_Residential
			case 233 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Soc1_3_3::RA_Residential
			case 237 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_4_1::para_t
			case 238 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "---";
				case 2 : return "---";
			} break;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_4_2::para_t
			case 241 :
			switch (t) {
				case 0 : return "---";
				case 1 : return "---";
			} break;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Soc1_4_3::para_t
			case 243 :
			switch (t) {
				case 0 : return "---";
				case 1 : return "---";
			} break;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
			} break;
			// Soc1_4_4::para_t
			case 246 :
			switch (t) {
				case 0 : return "---";
			} break;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_4_4::DGS_Logistics
			case 249 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_4_4::DGS_Production
			case 250 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc1_4_5::AL_LightingConcept
			case 251 :
			switch (t) {
				case 0 : return "";
			} break;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_4_6::SED_Residential
			case 253 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Soc1_6_1::para_t
			case 255 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_6_2::para_t
			case 257 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
			} break;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Soc1_6_3::para_t
			case 260 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
				case 9 : return "";
			} break;
			// Soc1_6_4::para_t
			case 262 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Soc1_6_5::para_t
			case 264 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
			} break;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Soc2_1_1::para_t
			case 270 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Socioculture::para_weights
			case 272 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Socioculture::para_goals
			case 273 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
				case 4 : return "-";
				case 5 : return "-";
			} break;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
			} break;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec1_3_3::para_t
			case 277 :
			switch (t) {
				case 0 : return "1/h";
				case 1 : return "m3/(hm2)";
			} break;
			// Tec1_3_3::ABE_Measuring
			case 278 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec1_3_4::para_t
			case 279 :
			switch (t) {
				case 0 : return "---";
			} break;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec1_4_1::PS_Planning
			case 282 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
			} break;
			// Tec1_4_1::PS_Implementation
			case 283 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
			} break;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
			} break;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_4_5::URE_EnergySources
			case 294 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_4_5::URE_Production
			case 295 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
			} break;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Tec1_6_3::para_t
			case 307 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
			} break;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec3_1_1::MI_MobilityConcept
			case 315 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
			} break;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
			} break;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec3_1_3::para_t
			case 320 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "---";
				case 3 : return "---";
				case 4 : return "-";
				case 5 : return "---";
			} break;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 :
			switch (t) {
				case 0 : return "";
			} break;
			// Tec3_1_4::para_t
			case 325 :
			switch (t) {
				case 0 : return "-";
			} break;
			// Tec3_1_4::RS_MobilitySharing
			case 326 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
			} break;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
			} break;
			// Technology::para_weights
			case 328 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
			} break;
			// Technology::para_goals
			case 329 :
			switch (t) {
				case 0 : return "-";
				case 1 : return "-";
				case 2 : return "-";
				case 3 : return "-";
			} break;
			// Utilities::UsageType
			case 330 :
			switch (t) {
				case 0 : return "";
				case 1 : return "";
				case 2 : return "";
				case 3 : return "";
				case 4 : return "";
				case 5 : return "";
				case 6 : return "";
				case 7 : return "";
				case 8 : return "";
				case 9 : return "";
				case 10 : return "";
			} break;
		} // switch
		throw IBK::Exception(IBK::FormatString("Cannot determine default unit for enumeration type '%1' and index '%2'.")
			.arg(enumtype).arg(t), "[KeywordList::Unit]");
	}

	const char * KeywordList::Color(const char * const enumtype, int t) {
		switch (enum2index(enumtype)) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Eco1_1_2::para_t
			case 3 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Eco1_1_3::para_t
			case 6 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Eco1_1_3::BRLCC_Calculation
			case 7 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
			} break;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Eco2_4_3::para_t
			case 13 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_4::para_t
			case 16 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_7::A2030_Expandability
			case 23 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Eco2_7_3::PPBIM_Preparation
			case 41 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Eco2_7_3::PPBIM_Creation
			case 42 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Economy::para_weights
			case 50 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Economy::para_goals
			case 51 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_2::para_t
			case 59 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_3::para_t
			case 66 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
				case 9 : return "#FFFFFF";
			} break;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_2_1::para_t
			case 69 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env1_2_1::EFM_A
			case 70 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Env1_2_1::EFM_Agenda2030
			case 73 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_3_2::para_t
			case 78 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_2_2::para_t
			case 85 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_2_5::para_t
			case 89 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env2_3_2::para_t
			case 93 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_2::para_t
			case 99 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_3::para_t
			case 105 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Environment::para_weights
			case 116 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Environment::para_goals
			case 117 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// KeywordList::MyParameters
			case 118 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_1_1::RP_Basis
			case 119 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_1_1::RP_RP
			case 120 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro1_1_2::A2030_Participation
			case 122 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro1_6_3::HAA_Recognition
			case 137 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_1_1::NRCS_Concept
			case 138 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_2::DRCS_Concept
			case 141 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_3::SGPCS_Concept
			case 144 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_4::WRCS_Concept
			case 147 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCWU_Concept
			case 155 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCEU_Concept
			case 159 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_1_7::M_Prevention
			case 162 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_3_1::TM_PlanningPhase
			case 163 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_3_3::TrialOperation
			case 165 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_3_6::OperationStartUpManagement
			case 168 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_3_7::BuildingPerformance
			case 169 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_5_1::FM_Check
			case 170 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_5_5::SIS_Implementation
			case 174 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Pro2_5_6::OCP_Extended
			case 176 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Process::para_weights
			case 177 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Process::para_goals
			case 178 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Site::para_weights
			case 179 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site::para_goals
			case 180 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_Screening
			case 182 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_DataBasis
			case 186 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Site1_1_1::CR_ResultApplication
			case 187 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_1_3::EEI_AirQuality
			case 190 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Site1_1_3::EEI_Radon
			case 191 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Site1_3_1::MIT_Surroundings
			case 192 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_3_2::PT_Stations
			case 194 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_3_2::PT_Intervals
			case 196 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_3_2::PT_RelationToBuilding
			case 197 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_3_3::BT_Connection
			case 199 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_3_3::BT_RelationToBuilding
			case 200 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_3_4::FT_SignageSystems
			case 203 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_3_5::AS_Within350Meters
			case 204 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
				case 9 : return "#FFFFFF";
				case 10 : return "#FFFFFF";
				case 11 : return "#FFFFFF";
			} break;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
			} break;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
				case 9 : return "#FFFFFF";
				case 10 : return "#FFFFFF";
				case 11 : return "#FFFFFF";
				case 12 : return "#FFFFFF";
				case 13 : return "#FFFFFF";
				case 14 : return "#FFFFFF";
				case 15 : return "#FFFFFF";
				case 16 : return "#FFFFFF";
				case 17 : return "#FFFFFF";
				case 18 : return "#FFFFFF";
			} break;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_1_1::para_t
			case 212 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
			} break;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_1_3::D_CoolingPeriod
			case 216 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
			} break;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_1_6::UI_UserInfluence
			case 219 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Soc1_1_Alt::AC_Innovation
			case 220 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_2_1::para_t
			case 221 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_2_2::para_t
			case 226 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
				case 9 : return "#FFFFFF";
				case 10 : return "#FFFFFF";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_3_1::ORSR_Office
			case 232 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_3_1::ORSR_Residential
			case 233 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Soc1_3_3::RA_Residential
			case 237 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_4_1::para_t
			case 238 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_4_2::para_t
			case 241 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Soc1_4_3::para_t
			case 243 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
			} break;
			// Soc1_4_4::para_t
			case 246 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_4_4::DGS_Logistics
			case 249 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_4_4::DGS_Production
			case 250 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_4_5::AL_LightingConcept
			case 251 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_4_6::SED_Residential
			case 253 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Soc1_6_1::para_t
			case 255 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_6_2::para_t
			case 257 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Soc1_6_3::para_t
			case 260 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
				case 9 : return "#FFFFFF";
			} break;
			// Soc1_6_4::para_t
			case 262 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Soc1_6_5::para_t
			case 264 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Soc2_1_1::para_t
			case 270 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Socioculture::para_weights
			case 272 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Socioculture::para_goals
			case 273 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
			} break;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec1_3_3::para_t
			case 277 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_3_3::ABE_Measuring
			case 278 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec1_3_4::para_t
			case 279 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec1_4_1::PS_Planning
			case 282 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
			} break;
			// Tec1_4_1::PS_Implementation
			case 283 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
			} break;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
			} break;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_4_5::URE_EnergySources
			case 294 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_4_5::URE_Production
			case 295 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Tec1_6_3::para_t
			case 307 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec3_1_1::MI_MobilityConcept
			case 315 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
			} break;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
			} break;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec3_1_3::para_t
			case 320 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
			} break;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec3_1_4::para_t
			case 325 :
			switch (t) {
				case 0 : return "#FFFFFF";
			} break;
			// Tec3_1_4::RS_MobilitySharing
			case 326 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
			} break;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Technology::para_weights
			case 328 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Technology::para_goals
			case 329 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
			} break;
			// Utilities::UsageType
			case 330 :
			switch (t) {
				case 0 : return "#FFFFFF";
				case 1 : return "#FFFFFF";
				case 2 : return "#FFFFFF";
				case 3 : return "#FFFFFF";
				case 4 : return "#FFFFFF";
				case 5 : return "#FFFFFF";
				case 6 : return "#FFFFFF";
				case 7 : return "#FFFFFF";
				case 8 : return "#FFFFFF";
				case 9 : return "#FFFFFF";
				case 10 : return "#FFFFFF";
			} break;
		} // switch
		throw IBK::Exception(IBK::FormatString("Cannot determine color for enumeration type '%1' and index '%2'.")
			.arg(enumtype).arg(t), "[KeywordList::Color]");
	}

	double KeywordList::DefaultValue(const char * const enumtype, int t) {
		switch (enum2index(enumtype)) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_2::para_t
			case 3 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_3::para_t
			case 6 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco1_1_3::BRLCC_Calculation
			case 7 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_3::para_t
			case 13 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_4::para_t
			case 16 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_7::A2030_Expandability
			case 23 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_3::PPBIM_Preparation
			case 41 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_3::PPBIM_Creation
			case 42 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Economy::para_weights
			case 50 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Economy::para_goals
			case 51 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::para_t
			case 59 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_3::para_t
			case 66 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
				case 9 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_2_1::para_t
			case 69 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_2_1::EFM_A
			case 70 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_2_1::EFM_Agenda2030
			case 73 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_2::para_t
			case 78 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_2::para_t
			case 85 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_5::para_t
			case 89 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_3_2::para_t
			case 93 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_2::para_t
			case 99 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_3::para_t
			case 105 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Environment::para_weights
			case 116 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Environment::para_goals
			case 117 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// KeywordList::MyParameters
			case 118 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_1_1::RP_Basis
			case 119 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_1_1::RP_RP
			case 120 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_1_2::A2030_Participation
			case 122 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro1_6_3::HAA_Recognition
			case 137 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_1::NRCS_Concept
			case 138 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_2::DRCS_Concept
			case 141 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_3::SGPCS_Concept
			case 144 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_4::WRCS_Concept
			case 147 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCWU_Concept
			case 155 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCEU_Concept
			case 159 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_1_7::M_Prevention
			case 162 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_1::TM_PlanningPhase
			case 163 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_3::TrialOperation
			case 165 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_6::OperationStartUpManagement
			case 168 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_3_7::BuildingPerformance
			case 169 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_1::FM_Check
			case 170 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_5::SIS_Implementation
			case 174 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Pro2_5_6::OCP_Extended
			case 176 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Process::para_weights
			case 177 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Process::para_goals
			case 178 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site::para_weights
			case 179 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site::para_goals
			case 180 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_Screening
			case 182 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_DataBasis
			case 186 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_1::CR_ResultApplication
			case 187 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_3::EEI_AirQuality
			case 190 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_1_3::EEI_Radon
			case 191 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_1::MIT_Surroundings
			case 192 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_2::PT_Stations
			case 194 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_2::PT_Intervals
			case 196 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_2::PT_RelationToBuilding
			case 197 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_3::BT_Connection
			case 199 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_3::BT_RelationToBuilding
			case 200 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_4::FT_SignageSystems
			case 203 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_5::AS_Within350Meters
			case 204 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
				case 9 : return std::numeric_limits<double>::quiet_NaN();
				case 10 : return std::numeric_limits<double>::quiet_NaN();
				case 11 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
				case 9 : return std::numeric_limits<double>::quiet_NaN();
				case 10 : return std::numeric_limits<double>::quiet_NaN();
				case 11 : return std::numeric_limits<double>::quiet_NaN();
				case 12 : return std::numeric_limits<double>::quiet_NaN();
				case 13 : return std::numeric_limits<double>::quiet_NaN();
				case 14 : return std::numeric_limits<double>::quiet_NaN();
				case 15 : return std::numeric_limits<double>::quiet_NaN();
				case 16 : return std::numeric_limits<double>::quiet_NaN();
				case 17 : return std::numeric_limits<double>::quiet_NaN();
				case 18 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_1::para_t
			case 212 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_3::D_CoolingPeriod
			case 216 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_6::UI_UserInfluence
			case 219 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_1_Alt::AC_Innovation
			case 220 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_1::para_t
			case 221 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_2::para_t
			case 226 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
				case 9 : return std::numeric_limits<double>::quiet_NaN();
				case 10 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_1::ORSR_Office
			case 232 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_1::ORSR_Residential
			case 233 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_3_3::RA_Residential
			case 237 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_1::para_t
			case 238 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_2::para_t
			case 241 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_3::para_t
			case 243 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_4::para_t
			case 246 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_4::DGS_Logistics
			case 249 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_4::DGS_Production
			case 250 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_5::AL_LightingConcept
			case 251 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_6::SED_Residential
			case 253 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_1::para_t
			case 255 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_2::para_t
			case 257 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_3::para_t
			case 260 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
				case 9 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_4::para_t
			case 262 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_5::para_t
			case 264 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc2_1_1::para_t
			case 270 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Socioculture::para_weights
			case 272 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Socioculture::para_goals
			case 273 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_3::para_t
			case 277 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_3::ABE_Measuring
			case 278 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_4::para_t
			case 279 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_1::PS_Planning
			case 282 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_1::PS_Implementation
			case 283 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_5::URE_EnergySources
			case 294 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_4_5::URE_Production
			case 295 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::para_t
			case 307 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_1::MI_MobilityConcept
			case 315 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_3::para_t
			case 320 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_4::para_t
			case 325 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_4::RS_MobilitySharing
			case 326 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Technology::para_weights
			case 328 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Technology::para_goals
			case 329 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
			} break;
			// Utilities::UsageType
			case 330 :
			switch (t) {
				case 0 : return std::numeric_limits<double>::quiet_NaN();
				case 1 : return std::numeric_limits<double>::quiet_NaN();
				case 2 : return std::numeric_limits<double>::quiet_NaN();
				case 3 : return std::numeric_limits<double>::quiet_NaN();
				case 4 : return std::numeric_limits<double>::quiet_NaN();
				case 5 : return std::numeric_limits<double>::quiet_NaN();
				case 6 : return std::numeric_limits<double>::quiet_NaN();
				case 7 : return std::numeric_limits<double>::quiet_NaN();
				case 8 : return std::numeric_limits<double>::quiet_NaN();
				case 9 : return std::numeric_limits<double>::quiet_NaN();
				case 10 : return std::numeric_limits<double>::quiet_NaN();
			} break;
		} // switch
		throw IBK::Exception(IBK::FormatString("Cannot determine default value for enumeration type '%1' and index '%2'.")
			.arg(enumtype).arg(t), "[KeywordList::DefaultValue]");
	}

	// number of entries in a keyword list
	unsigned int KeywordList::Count(const char * const enumtype) {
		switch (enum2index(enumtype)) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 : return 2;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 : return 1;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 : return 5;
			// Eco1_1_2::para_t
			case 3 : return 1;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 : return 2;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 : return 4;
			// Eco1_1_3::para_t
			case 6 : return 6;
			// Eco1_1_3::BRLCC_Calculation
			case 7 : return 3;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 : return 3;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 : return 2;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 : return 7;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 : return 2;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 : return 6;
			// Eco2_4_3::para_t
			case 13 : return 1;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 : return 1;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 : return 1;
			// Eco2_4_4::para_t
			case 16 : return 3;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 : return 4;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 : return 2;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 : return 1;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 : return 1;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 : return 2;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 : return 1;
			// Eco2_4_7::A2030_Expandability
			case 23 : return 1;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 : return 1;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 : return 1;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 : return 2;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 : return 1;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 : return 4;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 : return 5;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 : return 2;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 : return 2;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 : return 3;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 : return 4;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 : return 1;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 : return 3;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 : return 5;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 : return 1;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 : return 1;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 : return 3;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 : return 3;
			// Eco2_7_3::PPBIM_Preparation
			case 41 : return 6;
			// Eco2_7_3::PPBIM_Creation
			case 42 : return 4;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 : return 2;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 : return 1;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 : return 1;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 : return 4;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 : return 1;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 : return 1;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 : return 1;
			// Economy::para_weights
			case 50 : return 4;
			// Economy::para_goals
			case 51 : return 4;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 : return 4;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 : return 5;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 : return 3;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 : return 5;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 : return 1;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 : return 1;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 : return 1;
			// Env1_1_2::para_t
			case 59 : return 4;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 : return 2;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 : return 1;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 : return 1;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 : return 1;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 : return 3;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 : return 1;
			// Env1_1_3::para_t
			case 66 : return 10;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 : return 1;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 : return 1;
			// Env1_2_1::para_t
			case 69 : return 2;
			// Env1_2_1::EFM_A
			case 70 : return 5;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 : return 5;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 : return 5;
			// Env1_2_1::EFM_Agenda2030
			case 73 : return 5;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 : return 1;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 : return 1;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 : return 1;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 : return 1;
			// Env1_3_2::para_t
			case 78 : return 6;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 : return 1;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 : return 2;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 : return 1;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 : return 1;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 : return 6;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 : return 2;
			// Env2_2_2::para_t
			case 85 : return 2;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 : return 1;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 : return 2;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 : return 1;
			// Env2_2_5::para_t
			case 89 : return 3;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 : return 3;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 : return 4;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 : return 3;
			// Env2_3_2::para_t
			case 93 : return 1;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 : return 2;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 : return 1;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 : return 3;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 : return 3;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 : return 1;
			// Env2_4_2::para_t
			case 99 : return 3;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 : return 1;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 : return 1;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 : return 1;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 : return 2;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 : return 1;
			// Env2_4_3::para_t
			case 105 : return 1;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 : return 2;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 : return 2;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 : return 1;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 : return 1;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 : return 4;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 : return 1;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 : return 1;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 : return 6;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 : return 2;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 : return 1;
			// Environment::para_weights
			case 116 : return 6;
			// Environment::para_goals
			case 117 : return 6;
			// KeywordList::MyParameters
			case 118 : return 2;
			// Pro1_1_1::RP_Basis
			case 119 : return 2;
			// Pro1_1_1::RP_RP
			case 120 : return 3;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 : return 1;
			// Pro1_1_2::A2030_Participation
			case 122 : return 6;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 : return 2;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 : return 4;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 : return 1;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 : return 1;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 : return 2;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 : return 2;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 : return 2;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 : return 1;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 : return 3;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 : return 2;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 : return 2;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 : return 3;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 : return 3;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 : return 2;
			// Pro1_6_3::HAA_Recognition
			case 137 : return 2;
			// Pro2_1_1::NRCS_Concept
			case 138 : return 1;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 : return 1;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 : return 1;
			// Pro2_1_2::DRCS_Concept
			case 141 : return 1;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 : return 1;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 : return 1;
			// Pro2_1_3::SGPCS_Concept
			case 144 : return 1;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 : return 1;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 : return 1;
			// Pro2_1_4::WRCS_Concept
			case 147 : return 1;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 : return 1;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 : return 1;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 : return 1;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 : return 1;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 : return 1;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 : return 5;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 : return 1;
			// Pro2_1_6::RCWU_Concept
			case 155 : return 1;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 : return 1;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 : return 1;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 : return 1;
			// Pro2_1_6::RCEU_Concept
			case 159 : return 1;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 : return 1;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 : return 1;
			// Pro2_1_7::M_Prevention
			case 162 : return 1;
			// Pro2_3_1::TM_PlanningPhase
			case 163 : return 2;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 : return 2;
			// Pro2_3_3::TrialOperation
			case 165 : return 2;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 : return 2;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 : return 1;
			// Pro2_3_6::OperationStartUpManagement
			case 168 : return 1;
			// Pro2_3_7::BuildingPerformance
			case 169 : return 1;
			// Pro2_5_1::FM_Check
			case 170 : return 1;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 : return 3;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 : return 1;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 : return 2;
			// Pro2_5_5::SIS_Implementation
			case 174 : return 2;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 : return 2;
			// Pro2_5_6::OCP_Extended
			case 176 : return 1;
			// Process::para_weights
			case 177 : return 6;
			// Process::para_goals
			case 178 : return 6;
			// Site::para_weights
			case 179 : return 3;
			// Site::para_goals
			case 180 : return 3;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 : return 2;
			// Site1_1_1::CR_Screening
			case 182 : return 3;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 : return 3;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 : return 2;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 : return 1;
			// Site1_1_1::CR_DataBasis
			case 186 : return 4;
			// Site1_1_1::CR_ResultApplication
			case 187 : return 1;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 : return 1;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 : return 3;
			// Site1_1_3::EEI_AirQuality
			case 190 : return 5;
			// Site1_1_3::EEI_Radon
			case 191 : return 4;
			// Site1_3_1::MIT_Surroundings
			case 192 : return 3;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 : return 1;
			// Site1_3_2::PT_Stations
			case 194 : return 1;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 : return 3;
			// Site1_3_2::PT_Intervals
			case 196 : return 3;
			// Site1_3_2::PT_RelationToBuilding
			case 197 : return 3;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 : return 2;
			// Site1_3_3::BT_Connection
			case 199 : return 2;
			// Site1_3_3::BT_RelationToBuilding
			case 200 : return 1;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 : return 3;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 : return 2;
			// Site1_3_4::FT_SignageSystems
			case 203 : return 2;
			// Site1_3_5::AS_Within350Meters
			case 204 : return 2;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 : return 1;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 : return 1;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 : return 12;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 : return 3;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 : return 7;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 : return 19;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 : return 2;
			// Soc1_1_1::para_t
			case 212 : return 1;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 : return 7;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 : return 3;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 : return 1;
			// Soc1_1_3::D_CoolingPeriod
			case 216 : return 2;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 : return 7;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 : return 2;
			// Soc1_1_6::UI_UserInfluence
			case 219 : return 4;
			// Soc1_1_Alt::AC_Innovation
			case 220 : return 1;
			// Soc1_2_1::para_t
			case 221 : return 4;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 : return 6;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 : return 3;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 : return 2;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 : return 3;
			// Soc1_2_2::para_t
			case 226 : return 2;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 : return 11;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 : return 6;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 : return 3;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 : return 4;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 : return 1;
			// Soc1_3_1::ORSR_Office
			case 232 : return 1;
			// Soc1_3_1::ORSR_Residential
			case 233 : return 2;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 : return 1;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 : return 1;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 : return 5;
			// Soc1_3_3::RA_Residential
			case 237 : return 2;
			// Soc1_4_1::para_t
			case 238 : return 3;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 : return 2;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 : return 2;
			// Soc1_4_2::para_t
			case 241 : return 2;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 : return 4;
			// Soc1_4_3::para_t
			case 243 : return 2;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 : return 5;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 : return 9;
			// Soc1_4_4::para_t
			case 246 : return 1;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 : return 5;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 : return 1;
			// Soc1_4_4::DGS_Logistics
			case 249 : return 3;
			// Soc1_4_4::DGS_Production
			case 250 : return 2;
			// Soc1_4_5::AL_LightingConcept
			case 251 : return 1;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 : return 3;
			// Soc1_4_6::SED_Residential
			case 253 : return 3;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 : return 4;
			// Soc1_6_1::para_t
			case 255 : return 1;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 : return 3;
			// Soc1_6_2::para_t
			case 257 : return 2;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 : return 6;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 : return 3;
			// Soc1_6_3::para_t
			case 260 : return 1;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 : return 10;
			// Soc1_6_4::para_t
			case 262 : return 1;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 : return 5;
			// Soc1_6_5::para_t
			case 264 : return 2;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 : return 8;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 : return 5;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 : return 9;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 : return 6;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 : return 2;
			// Soc2_1_1::para_t
			case 270 : return 1;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 : return 3;
			// Socioculture::para_weights
			case 272 : return 6;
			// Socioculture::para_goals
			case 273 : return 6;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 : return 6;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 : return 9;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 : return 3;
			// Tec1_3_3::para_t
			case 277 : return 2;
			// Tec1_3_3::ABE_Measuring
			case 278 : return 3;
			// Tec1_3_4::para_t
			case 279 : return 1;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 : return 4;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 : return 3;
			// Tec1_4_1::PS_Planning
			case 282 : return 7;
			// Tec1_4_1::PS_Implementation
			case 283 : return 7;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 : return 5;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 : return 5;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 : return 3;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 : return 2;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 : return 2;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 : return 8;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 : return 4;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 : return 1;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 : return 2;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 : return 2;
			// Tec1_4_5::URE_EnergySources
			case 294 : return 2;
			// Tec1_4_5::URE_Production
			case 295 : return 6;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 : return 1;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 : return 1;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 : return 3;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 : return 2;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 : return 4;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 : return 1;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 : return 1;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 : return 1;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 : return 2;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 : return 2;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 : return 4;
			// Tec1_6_3::para_t
			case 307 : return 2;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 : return 1;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 : return 2;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 : return 2;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 : return 5;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 : return 4;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 : return 2;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 : return 3;
			// Tec3_1_1::MI_MobilityConcept
			case 315 : return 2;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 : return 2;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 : return 3;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 : return 5;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 : return 1;
			// Tec3_1_3::para_t
			case 320 : return 6;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 : return 1;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 : return 1;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 : return 2;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 : return 1;
			// Tec3_1_4::para_t
			case 325 : return 1;
			// Tec3_1_4::RS_MobilitySharing
			case 326 : return 2;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 : return 4;
			// Technology::para_weights
			case 328 : return 4;
			// Technology::para_goals
			case 329 : return 4;
			// Utilities::UsageType
			case 330 : return 11;
		} // switch
		throw IBK::Exception(IBK::FormatString("Invalid enumeration type '%1'.")
			.arg(enumtype), "[KeywordList::Count]");
	}

	// max index for entries sharing a category in a keyword list
	int KeywordList::MaxIndex(const char * const enumtype) {
		switch (enum2index(enumtype)) {
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessEarlyStages
			case 0 : return 1;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessLCCostOptimisation
			case 1 : return 0;
			// Eco1_1_1::LCCCP_IntegrationOfLCCCDuringPlanningProcessPartialExamination
			case 2 : return 4;
			// Eco1_1_2::para_t
			case 3 : return 0;
			// Eco1_1_2::EECBO_BuildingEnergyBill
			case 4 : return 1;
			// Eco1_1_2::EECBO_CircularEconomyBonusReuse
			case 5 : return 3;
			// Eco1_1_3::para_t
			case 6 : return 5;
			// Eco1_1_3::BRLCC_Calculation
			case 7 : return 2;
			// Eco2_4_1::ASBC_SiteAnalysis
			case 8 : return 2;
			// Eco2_4_1::ASBC_BuildingConceptAndSynergies
			case 9 : return 1;
			// Eco2_4_1::ASBC_HealthcareBuildingConceptAndSynergies
			case 10 : return 6;
			// Eco2_4_2::ATPUS_ProofOfReusability
			case 11 : return 1;
			// Eco2_4_2::ATPUS_ProofOfAdaptabilityOfIndividualFactors
			case 12 : return 5;
			// Eco2_4_3::para_t
			case 13 : return 0;
			// Eco2_4_3::DUTTC_DegreeOfUseOrTenancy
			case 14 : return 0;
			// Eco2_4_3::DUTTC_CircularEconomyUsersAndTenants
			case 15 : return 0;
			// Eco2_4_4::para_t
			case 16 : return 2;
			// Eco2_4_4::SE_RatioOfUsableSpaceToGroundSpace
			case 17 : return 3;
			// Eco2_4_4::SE_MultipleUseOfSpace
			case 18 : return 1;
			// Eco2_4_4::SE_Agenda2030BonusSufficiency
			case 19 : return 0;
			// Eco2_4_5::RA_RiskAnalysisAccordingToEuropeanFramework
			case 20 : return 0;
			// Eco2_4_5::RA_BuildingConformToTaxonomy
			case 21 : return 1;
			// Eco2_4_6::A2030C_DigitalInfrastructure
			case 22 : return 0;
			// Eco2_4_7::A2030_Expandability
			case 23 : return 0;
			// Eco2_4_7::A2030_ImpulsAttractor
			case 24 : return 0;
			// Eco2_6_1::BCRMPV_PrePlanningphase4
			case 25 : return 0;
			// Eco2_6_1::BCRMPV_PostPlanningphase4
			case 26 : return 1;
			// Eco2_6_1::Agenda2030_CostBenefitAnalysis
			case 27 : return 0;
			// Eco2_6_2::ACC_QuantitativeEvaluationOfMeasures
			case 28 : return 3;
			// Eco2_6_2::ACC_QualityOfImplementedAdaptationMeasures
			case 29 : return 4;
			// Eco2_6_2::ACC_GeneralResilienceToElementalDamages
			case 30 : return 1;
			// Eco2_6_2::ACC_Agenda2030HeadLoad
			case 31 : return 1;
			// Eco2_6_3::MAFERS_CompensationMeasuresAirQuality
			case 32 : return 2;
			// Eco2_6_3::MAFERS_CompensationMeasuresNoise
			case 33 : return 3;
			// Eco2_6_3::MAFERS_RadonRiskReduction
			case 34 : return 0;
			// Eco2_7_1::DCB_CurrentPlanningData
			case 35 : return 2;
			// Eco2_7_1::DCB_CompleteSustainabilityBuildingDocumentation
			case 36 : return 4;
			// Eco2_7_1::DCB_CircularEconomyDataBasisForUrbanMines
			case 37 : return 0;
			// Eco2_7_1::DCB_Agenda2030DigitalFootprint
			case 38 : return 0;
			// Eco2_7_2::ODBU_RevisionOperationMaintenancePlan
			case 39 : return 2;
			// Eco2_7_2::ODBU_OperatorFriendlyBuildingModel
			case 40 : return 2;
			// Eco2_7_3::PPBIM_Preparation
			case 41 : return 5;
			// Eco2_7_3::PPBIM_Creation
			case 42 : return 3;
			// Eco2_7_3::PPBIM_SustainabilityOptimisationWithBIM
			case 43 : return 1;
			// Eco2_7_3::PPBIM_CircularEconomyBIM2FMOperatorConcept
			case 44 : return 0;
			// Eco2_7_3::PPBIM_Agenda2030SustainabilityCheck
			case 45 : return 0;
			// Eco2_7_4::DTOP_CreationAndHandoverOfAsBuiltDocumentationOrBuildingModel
			case 46 : return 3;
			// Eco2_7_4::DTOP_CircularEconomyDigitalisationOfPreexistingConstructions
			case 47 : return 0;
			// Eco2_7_5::DC_InformationOnBuildingRemovability
			case 48 : return 0;
			// Eco2_7_Alt::AC_CircularDigitalTwin
			case 49 : return 0;
			// Economy::para_weights
			case 50 : return 3;
			// Economy::para_goals
			case 51 : return 3;
			// Env1_1_1::CO2EarlyStage_OperatingEvaluation
			case 52 : return 3;
			// Env1_1_1::CO2EarlyStage_FurtherVariants
			case 53 : return 4;
			// Env1_1_1::CO2PlanningStage_OperatingEvaluation
			case 54 : return 2;
			// Env1_1_1::CO2PlanningStage_FurtherVariants
			case 55 : return 4;
			// Env1_1_1::CO2PlanningStage_EmissionOptimization
			case 56 : return 0;
			// Env1_1_1::CO2Agenda2030_IntegrationOfPreexistingBuilding
			case 57 : return 0;
			// Env1_1_1::CO2Agenda2030MobilityOptimization
			case 58 : return 0;
			// Env1_1_2::para_t
			case 59 : return 3;
			// Env1_1_2::LCCO2_DisclosureOfLifeCycleBalances
			case 60 : return 1;
			// Env1_1_2::LCCO2_InterpolationOfEvaluationResultBasedOnReferenceValue
			case 61 : return 0;
			// Env1_1_2::LCCO2Agenda2030_LifeCycleClimateProtectionAgenda
			case 62 : return 0;
			// Env1_1_2::LCCO2Agenda2030_ClimateProtectionThroughSufficiency
			case 63 : return 0;
			// Env1_1_2::LCCO2BalanceFrameworkOperation_ClimateProtectionAgendaClimateNeutralOperation
			case 64 : return 2;
			// Env1_1_2::LCCO2BalanceFrameworkStructure_CO2ReducedConstructionPhase
			case 65 : return 0;
			// Env1_1_3::para_t
			case 66 : return 9;
			// Env1_1_3::CVAEI_LifeCyclePrimaryEnergyBalance
			case 67 : return 0;
			// Env1_1_3::CVAEI_WeightedResultsOfAdditionalEnvironmentalIndicators
			case 68 : return 0;
			// Env1_2_1::para_t
			case 69 : return 1;
			// Env1_2_1::EFM_A
			case 70 : return 4;
			// Env1_2_1::EFM_BResidentialCommercial
			case 71 : return 4;
			// Env1_2_1::EFM_BShoppingCenter
			case 72 : return 4;
			// Env1_2_1::EFM_Agenda2030
			case 73 : return 4;
			// Env1_2_1::EFM_ExtraPointsForQS123
			case 74 : return 0;
			// Env1_3_1::RURPE_SupplyChainDiligence
			case 75 : return 0;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInPlanning
			case 76 : return 0;
			// Env1_3_1::RURPE_ResponsibleUsageOfResourcesInExecutionAndDocumentation
			case 77 : return 0;
			// Env1_3_2::para_t
			case 78 : return 5;
			// Env1_3_2::RRM_CompanyResponsibilityForResourceManagement
			case 79 : return 0;
			// Env1_3_2::RRM_UsageOfResponsiblyWonProductsSecondaryResources
			case 80 : return 1;
			// Env1_3_2::RRM_PercentageOfWoodMaterialsFromSustainableForestry
			case 81 : return 0;
			// Env1_3_2::RRM_PRCEWMPS
			case 82 : return 0;
			// Env2_2_1::DWDWWV_SuperordinateConceptForWaterUsage
			case 83 : return 5;
			// Env2_2_1::DWDWWV_UpdatesToSuperordinateConcept
			case 84 : return 1;
			// Env2_2_2::para_t
			case 85 : return 1;
			// Env2_2_2::DWDWWV_WaterUsageIndex
			case 86 : return 0;
			// Env2_2_3::DWDWWV_IrrigatioAndRetention
			case 87 : return 1;
			// Env2_2_4::DWDWWV_DegreeOfIntegrationIntoQuartersInfrastructure
			case 88 : return 0;
			// Env2_2_5::para_t
			case 89 : return 2;
			// Env2_2_5::DWDWWV_ContributionToSpongeCity
			case 90 : return 2;
			// Env2_2_5::DWDWWV_DrinkingWaterSanitation
			case 91 : return 3;
			// Env2_3_1::AD_DegreeOfConversion
			case 92 : return 2;
			// Env2_3_2::para_t
			case 93 : return 0;
			// Env2_3_2::AD_DegreeOfSealingAndAdjustmentMeasures
			case 94 : return 1;
			// Env2_3_2::AD_CircularEconomyBonusUnsealing
			case 95 : return 0;
			// Env2_3_3::ADSQI_SoilRestoration
			case 96 : return 2;
			// Env2_3_3::ADSQI_CircularEconomyBonusInSituSoilRestorationAndProtection
			case 97 : return 2;
			// Env2_4_1::BDOS_CompilationAndExecutionOfBiodiversityStrategy
			case 98 : return 0;
			// Env2_4_2::para_t
			case 99 : return 2;
			// Env2_4_2::BDOS_BiotopeBiotopeSupportingArea
			case 100 : return 0;
			// Env2_4_2::BDOS_BiotopeGreenRoof
			case 101 : return 0;
			// Env2_4_2::BDOS_BiotopeAreaFactorAndAgenda2030VegetatedBuilding
			case 102 : return 0;
			// Env2_4_2::BDOS_DiversityOfStructures
			case 103 : return 1;
			// Env2_4_2::BDOS_Agenda2030BonusFertileSoil
			case 104 : return 0;
			// Env2_4_3::para_t
			case 105 : return 0;
			// Env2_4_3::BDOS_VegetationNoEmploymentOfInvasivePlantSpecies
			case 106 : return 1;
			// Env2_4_3::BDOS_VegetationEmploymentOfDiverseLocalSpeciesSuitedToSite
			case 107 : return 1;
			// Env2_4_3::BDOS_VegetationAgenda2030BonusPreservationOfVegetationWithHighEcologicalValue
			case 108 : return 0;
			// Env2_4_4::BDOS_RelationToSurroundingsBiotopeInterconnectivity
			case 109 : return 0;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesIlluminationConcept
			case 110 : return 3;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesAnimalTraps
			case 111 : return 0;
			// Env2_4_5::BDOS_ReductionOfNegativeInfluencesConstructionSitePlan
			case 112 : return 0;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringDevelopmentAndMaintenanceCareContract
			case 113 : return 5;
			// Env2_4_6::BDOS_PreparativeCareAndMonitoringMonitoringAndSuccessControl
			case 114 : return 1;
			// Env2_4_Alt::BDOS_AlternativeCertification
			case 115 : return 0;
			// Environment::para_weights
			case 116 : return 5;
			// Environment::para_goals
			case 117 : return 5;
			// KeywordList::MyParameters
			case 118 : return 1;
			// Pro1_1_1::RP_Basis
			case 119 : return 1;
			// Pro1_1_1::RP_RP
			case 120 : return 2;
			// Pro1_1_1::RP_Agenda2030FeasibilitySurvey
			case 121 : return 0;
			// Pro1_1_2::A2030_Participation
			case 122 : return 5;
			// Pro1_1_3::CS_SustainabilityRequirements
			case 123 : return 1;
			// Pro1_4_1::SATO_ExtentOfIntegration
			case 124 : return 3;
			// Pro1_4_1::SATO_CircularEconomyRecycledMaterials
			case 125 : return 0;
			// Pro1_6_1::CEV_PreemptiveExaminationOfVariantsOrPlanningCompetition
			case 126 : return 0;
			// Pro1_6_1::CEV_ConceptAssignmentMannerAndScopeOfMethod
			case 127 : return 1;
			// Pro1_6_1::CEV_ConceptAssignmentQualityEnsurance
			case 128 : return 1;
			// Pro1_6_1::CEV_MultipleAssignmentsScopeOfMethod
			case 129 : return 1;
			// Pro1_6_1::CEV_MultipleAssignmentsQualityEnsurance
			case 130 : return 0;
			// Pro1_6_1::CEV_MultipleAssignmentsImplementationOfAnAwardWinningDesign
			case 131 : return 2;
			// Pro1_6_1::CEV_PlanningCompetitionScopeAndQualityOfMethod
			case 132 : return 1;
			// Pro1_6_1::CEV_PlanningCompetitionMannerOfCompetitionMethod
			case 133 : return 1;
			// Pro1_6_1::CEV_PlanningCompetitionImplementationOfAnAwardWinningDesign
			case 134 : return 2;
			// Pro1_6_1::CEV_PlanningCompetitionCommissioningOfAwardWinnersPlanningTeam
			case 135 : return 2;
			// Pro1_6_2::R_RecommendationByIndependentDesignBoards
			case 136 : return 1;
			// Pro1_6_3::HAA_Recognition
			case 137 : return 1;
			// Pro2_1_1::NRCS_Concept
			case 138 : return 0;
			// Pro2_1_1::NRCS_InstructionOfOperators
			case 139 : return 0;
			// Pro2_1_1::NRCS_ExaminationOfImplementation
			case 140 : return 0;
			// Pro2_1_2::DRCS_Concept
			case 141 : return 0;
			// Pro2_1_2::DRCS_InstructionOfOperators
			case 142 : return 0;
			// Pro2_1_2::DRCS_ExaminationOfImplementation
			case 143 : return 0;
			// Pro2_1_3::SGPCS_Concept
			case 144 : return 0;
			// Pro2_1_3::SGPCS_InstructionOfOperators
			case 145 : return 0;
			// Pro2_1_3::SGPCS_ExaminationOfImplementation
			case 146 : return 0;
			// Pro2_1_4::WRCS_Concept
			case 147 : return 0;
			// Pro2_1_4::WRCS_InstructionOfOperators
			case 148 : return 0;
			// Pro2_1_4::WRCS_ExaminationOfImplementation
			case 149 : return 0;
			// Pro2_1_4::WRCS_CircularEconomyWastePrevention
			case 150 : return 0;
			// Pro2_1_5::C_ExternalSignageAndInformation
			case 151 : return 0;
			// Pro2_1_5::C_ExternalCommunicationWithResidents
			case 152 : return 0;
			// Pro2_1_5::C_InternalSharingOfInformation
			case 153 : return 4;
			// Pro2_1_6::RCWU_DataTransparency
			case 154 : return 0;
			// Pro2_1_6::RCWU_Concept
			case 155 : return 0;
			// Pro2_1_6::RCWU_InstructionOfOperators
			case 156 : return 0;
			// Pro2_1_6::RCWU_ExaminationOfImplementation
			case 157 : return 0;
			// Pro2_1_6::RCEU_DataTransparency
			case 158 : return 0;
			// Pro2_1_6::RCEU_Concept
			case 159 : return 0;
			// Pro2_1_6::RCEU_InstructionOfOperators
			case 160 : return 0;
			// Pro2_1_6::RCEU_ExaminationOfImplementation
			case 161 : return 0;
			// Pro2_1_7::M_Prevention
			case 162 : return 0;
			// Pro2_3_1::TM_PlanningPhase
			case 163 : return 1;
			// Pro2_3_2::TM_ConstructionPhase
			case 164 : return 1;
			// Pro2_3_3::TrialOperation
			case 165 : return 1;
			// Pro2_3_4::TM_FirstOperationPhase
			case 166 : return 1;
			// Pro2_3_5::TM_CompleteMonitoring
			case 167 : return 0;
			// Pro2_3_6::OperationStartUpManagement
			case 168 : return 0;
			// Pro2_3_7::BuildingPerformance
			case 169 : return 0;
			// Pro2_5_1::FM_Check
			case 170 : return 0;
			// Pro2_5_2::MaintenanceInspectionOperationAndServiceInstructions
			case 171 : return 2;
			// Pro2_5_3::FacilityManagerGuidebook
			case 172 : return 0;
			// Pro2_5_4::CWU_PreparationOfUserFriendlyBuildingOperation
			case 173 : return 1;
			// Pro2_5_5::SIS_Implementation
			case 174 : return 1;
			// Pro2_5_5::SIS_Agenda2030NatureExperienceAndKnowledgeImpartation
			case 175 : return 1;
			// Pro2_5_6::OCP_Extended
			case 176 : return 0;
			// Process::para_weights
			case 177 : return 5;
			// Process::para_goals
			case 178 : return 5;
			// Site::para_weights
			case 179 : return 2;
			// Site::para_goals
			case 180 : return 2;
			// Site1_1_1::CR_ConductionOfAnalysis
			case 181 : return 1;
			// Site1_1_1::CR_Screening
			case 182 : return 2;
			// Site1_1_1::CR_SettingTheEvaluationPeriod
			case 183 : return 2;
			// Site1_1_1::CR_ActingOnTheEvaluation
			case 184 : return 1;
			// Site1_1_1::CR_Agenda2030ClimateProtectionGoal
			case 185 : return 0;
			// Site1_1_1::CR_DataBasis
			case 186 : return 3;
			// Site1_1_1::CR_ResultApplication
			case 187 : return 0;
			// Site1_1_2::ECRS_CurrentAndFuturePhysicalRisksDueToEnvironmentAndClimateChange
			case 188 : return 0;
			// Site1_1_3::EEI_SurroundingNoise
			case 189 : return 2;
			// Site1_1_3::EEI_AirQuality
			case 190 : return 4;
			// Site1_1_3::EEI_Radon
			case 191 : return 3;
			// Site1_3_1::MIT_Surroundings
			case 192 : return 2;
			// Site1_3_1::MIT_RelationToBuilding
			case 193 : return 0;
			// Site1_3_2::PT_Stations
			case 194 : return 0;
			// Site1_3_2::PT_DistanceToNextTrainStationWithAtLeastHourlyDepartures
			case 195 : return 2;
			// Site1_3_2::PT_Intervals
			case 196 : return 2;
			// Site1_3_2::PT_RelationToBuilding
			case 197 : return 2;
			// Site1_3_3::BT_CycleTrackWithin500Meters
			case 198 : return 1;
			// Site1_3_3::BT_Connection
			case 199 : return 1;
			// Site1_3_3::BT_RelationToBuilding
			case 200 : return 0;
			// Site1_3_4::FT_WalkwayNetworkWithin350Meters
			case 201 : return 2;
			// Site1_3_4::FT_CrossingOptionsWithin350Meters
			case 202 : return 1;
			// Site1_3_4::FT_SignageSystems
			case 203 : return 1;
			// Site1_3_5::AS_Within350Meters
			case 204 : return 1;
			// Site1_3_5::AS_AccessibleDevelopmentOfRoutingToBuildingAndSurroundings
			case 205 : return 0;
			// Site1_3_6::A2030_UsageOfPreexistingLoadingInfrastructure
			case 206 : return 0;
			// Site1_4_1::SI_WithinQuarterOrSurroundings
			case 207 : return 11;
			// Site1_4_1::SI_OptionsToUseIndoorAndOutdoorBuildingSpaces
			case 208 : return 2;
			// Site1_4_2::POE_InfrastructureInQuarterOrSurroundings
			case 209 : return 6;
			// Site1_4_3::BAIUD_InHouseDiversity
			case 210 : return 18;
			// Site1_4_3::BAIUD_CircularEconomyOffersOfDailyNecessitiesAndExchange
			case 211 : return 1;
			// Soc1_1_1::para_t
			case 212 : return 0;
			// Soc1_1_1::OTRT_OperativeTemperatureCoolingPeriod
			case 213 : return 6;
			// Soc1_1_2::RH_RelativeHumidityHeatingPeriod
			case 214 : return 2;
			// Soc1_1_2::RH_RelativeHumidityCoolingPeriod
			case 215 : return 0;
			// Soc1_1_3::D_CoolingPeriod
			case 216 : return 1;
			// Soc1_1_4::RTAFT_CoolingPeriod
			case 217 : return 6;
			// Soc1_1_5::A2030CA_ResilientThermalComfort
			case 218 : return 1;
			// Soc1_1_6::UI_UserInfluence
			case 219 : return 3;
			// Soc1_1_Alt::AC_Innovation
			case 220 : return 0;
			// Soc1_2_1::para_t
			case 221 : return 3;
			// Soc1_2_1::IHTVOC_Measuring_OfficeEducationHotelAssemblyHealthcareResidentialLogisticsProduction
			case 222 : return 5;
			// Soc1_2_1::IHTVOC_ShoppingCenterCommercialBuildingConvenienceStore
			case 223 : return 2;
			// Soc1_2_1::IHTVOC_Agenda2030InteriorAirToxicMatterReductionHealthAndComfort
			case 224 : return 1;
			// Soc1_2_1::IHTVOC_WoodworkBonus
			case 225 : return 2;
			// Soc1_2_2::para_t
			case 226 : return 1;
			// Soc1_2_2::IH_AirChangeFrequencyOfficeEducationHotelAssemblyHealthcare
			case 227 : return 10;
			// Soc1_2_2::IH_AirChangeFrequencyShoppingCenterCommercialBuildingConvenienceStore
			case 228 : return 5;
			// Soc1_2_2::IH_AirChangeFrequencyResidential
			case 229 : return 2;
			// Soc1_2_2::IH_AirChangeLogisticsAndProduction
			case 230 : return 3;
			// Soc1_3_1::ORSR_HealthcareHotelAssembly
			case 231 : return 0;
			// Soc1_3_1::ORSR_Office
			case 232 : return 0;
			// Soc1_3_1::ORSR_Residential
			case 233 : return 1;
			// Soc1_3_1::BAM_OfficeEducationHotelAssemblyHealthcareResidential
			case 234 : return 0;
			// Soc1_3_2::PAAC_RoomAcousticConcepts
			case 235 : return 0;
			// Soc1_3_3::RA_HotelHealthcareAssemblyEducationOffice
			case 236 : return 4;
			// Soc1_3_3::RA_Residential
			case 237 : return 1;
			// Soc1_4_1::para_t
			case 238 : return 2;
			// Soc1_4_1::DS_OfficeEducationAssemblyResidentialHotelHealthcareProduction
			case 239 : return 1;
			// Soc1_4_1::DS_ConvenienceStoreShoppingCenterCommercialBuilding
			case 240 : return 1;
			// Soc1_4_2::para_t
			case 241 : return 1;
			// Soc1_4_2::ARUL_OfficeEducationAssemblyLogisticsHealthcare
			case 242 : return 3;
			// Soc1_4_3::para_t
			case 243 : return 1;
			// Soc1_4_3::LOSO_ConvenienceStoreCommercialBuildingShoppingCenter
			case 244 : return 4;
			// Soc1_4_3::LOSO_OfficeEducationHotelLogisticsAssemblyResidentialHealthcare
			case 245 : return 8;
			// Soc1_4_4::para_t
			case 246 : return 0;
			// Soc1_4_4::DGS_OfficeEducationAssembly1And2Healthcare
			case 247 : return 4;
			// Soc1_4_4::DGS_ConvenienceStore
			case 248 : return 0;
			// Soc1_4_4::DGS_Logistics
			case 249 : return 2;
			// Soc1_4_4::DGS_Production
			case 250 : return 1;
			// Soc1_4_5::AL_LightingConcept
			case 251 : return 0;
			// Soc1_4_5::AL_ImplementationOfPlannedConceptAndObservationOfRequirements
			case 252 : return 2;
			// Soc1_4_6::SED_Residential
			case 253 : return 2;
			// Soc1_4_6::SED_HotelHealthcare
			case 254 : return 3;
			// Soc1_6_1::para_t
			case 255 : return 0;
			// Soc1_6_1::CSO_CommunicationZoneMainUsage
			case 256 : return 2;
			// Soc1_6_2::para_t
			case 257 : return 1;
			// Soc1_6_2::AOU_AdditionalOffersAndServices
			case 258 : return 5;
			// Soc1_6_2::AOU_OrientationInformation
			case 259 : return 2;
			// Soc1_6_3::para_t
			case 260 : return 0;
			// Soc1_6_3::FCEF_OnSiteOffers
			case 261 : return 9;
			// Soc1_6_4::para_t
			case 262 : return 0;
			// Soc1_6_4::QS_InnerAllotmentAreas
			case 263 : return 4;
			// Soc1_6_5::para_t
			case 264 : return 1;
			// Soc1_6_5::QS_DesignConceptForOutdoorAreas
			case 265 : return 7;
			// Soc1_6_5::QS_OutdoorCommonAreas
			case 266 : return 4;
			// Soc1_6_5::QS_OutdoorCommonAreasSuitedToUse
			case 267 : return 8;
			// Soc1_6_5::QS_OutdoorCommonAreaComfort
			case 268 : return 5;
			// Soc1_6_5::QS_Agenda2030ClimateProtectionFactorOfSurfaceStructuresAndClimateProtectionOptimisationOfOutdoorAreas
			case 269 : return 1;
			// Soc2_1_1::para_t
			case 270 : return 0;
			// Soc2_1_1::AQS_TotalQualityStage
			case 271 : return 2;
			// Socioculture::para_weights
			case 272 : return 5;
			// Socioculture::para_goals
			case 273 : return 5;
			// Tec1_3_1::PABE_PotentialOfFrontElements
			case 274 : return 5;
			// Tec1_3_2::TOES_EnvelopeParts
			case 275 : return 8;
			// Tec1_3_2::TOES_ThermalBridgeSurcharge
			case 276 : return 2;
			// Tec1_3_3::para_t
			case 277 : return 1;
			// Tec1_3_3::ABE_Measuring
			case 278 : return 2;
			// Tec1_3_4::para_t
			case 279 : return 0;
			// Tec1_3_4::HIS_VerificationAndVariations
			case 280 : return 3;
			// Tec1_3_5::QA_MeasuringQualityControl
			case 281 : return 2;
			// Tec1_4_1::PS_Planning
			case 282 : return 6;
			// Tec1_4_1::PS_Implementation
			case 283 : return 6;
			// Tec1_4_2::AAOTIRE_Warmth
			case 284 : return 4;
			// Tec1_4_2::AAOTIRE_Cooling
			case 285 : return 4;
			// Tec1_4_3::ABS_SystemsEngineeringAndCreation
			case 286 : return 2;
			// Tec1_4_3::ABS_DuctsTracesAllocation
			case 287 : return 1;
			// Tec1_4_4::IS_StateAndUpgradability
			case 288 : return 1;
			// Tec1_4_4::IS_IntegratedFunctionsInSuperordinateSystems
			case 289 : return 7;
			// Tec1_4_4::IS_PlanningOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 290 : return 3;
			// Tec1_4_4::IS_ImplementationOfIntegrationOfTechnicalSystemsAndMediaIntoQuartersAndDirectSurroundings
			case 291 : return 0;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsQuarterSolution
			case 292 : return 1;
			// Tec1_4_4::IS_IntegrationOfEnergyInfrastructureIntoQuartersAndDirectSurroundingsNetworkableEnergySystem
			case 293 : return 1;
			// Tec1_4_5::URE_EnergySources
			case 294 : return 1;
			// Tec1_4_5::URE_Production
			case 295 : return 5;
			// Tec1_6_1::CC_ProjectIncludesDemolition
			case 296 : return 0;
			// Tec1_6_1::SSAPPD_Analysis
			case 297 : return 0;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusStockPreservationOrUse
			case 298 : return 2;
			// Tec1_6_1::SSAPPD_DemolitionJustification
			case 299 : return 1;
			// Tec1_6_1::SSAPPD_DemolitionExecution
			case 300 : return 3;
			// Tec1_6_1::SSAPPD_DemolitionAlternativeCertification
			case 301 : return 0;
			// Tec1_6_1::SSAPPD_CircularEconomyBonusReuseOnSite
			case 302 : return 0;
			// Tec1_6_2::CC_ProjectIncludesDemolition
			case 303 : return 0;
			// Tec1_6_2::CCCP_GoalAndFocusDefinition
			case 304 : return 1;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsEarlyPhase
			case 305 : return 1;
			// Tec1_6_2::CCCP_ProjectRelatedCircularDesignConceptsApprovalAndExecutionPhase
			case 306 : return 3;
			// Tec1_6_3::para_t
			case 307 : return 1;
			// Tec1_6_3::CC_ProjectIncludesDemolition
			case 308 : return 0;
			// Tec1_6_3::CCED_DescriptionOfCircularBuildingPropertiesBuildingPass
			case 309 : return 1;
			// Tec1_6_3::CCED_EvaluationOfRealisedCircularPropertiesOnBuildingLevel
			case 310 : return 1;
			// Tec1_6_3::CCED_UseOfCircularProductsOnConstructionElementLevel
			case 311 : return 4;
			// Tec1_6_3::CCED_CircularEconomyBonusRecyclingMaterialAppropriateConstructionAvoidanceOfMaterialMixingConstructiveIntegrations
			case 312 : return 3;
			// Tec1_6_3::CCED_ReuseRebuildingAndDemolitionInstructions
			case 313 : return 1;
			// Tec1_6_3::CCED_CircularEconomyBonusCircularBuildingAndAggregatedCircularityEvaluation
			case 314 : return 2;
			// Tec3_1_1::MI_MobilityConcept
			case 315 : return 1;
			// Tec3_1_2::I_PedestrianInfrastructure
			case 316 : return 1;
			// Tec3_1_2::I_BicycleInfrastructure
			case 317 : return 2;
			// Tec3_1_2::I_MotorisedIndividualTransport
			case 318 : return 4;
			// Tec3_1_2::I_Agenda2030MobilityManagementConcept
			case 319 : return 0;
			// Tec3_1_3::para_t
			case 320 : return 5;
			// Tec3_1_3::IAFS_BicycleTrafficAndElectricBicycles
			case 321 : return 0;
			// Tec3_1_3::IAFS_MotorisedIndividualTransport
			case 322 : return 0;
			// Tec3_1_3::IAFS_IntegrationOfLoadingOrTankStations
			case 323 : return 1;
			// Tec3_1_3::IAFS_Agenda2030ClimateProtectionGoals
			case 324 : return 0;
			// Tec3_1_4::para_t
			case 325 : return 0;
			// Tec3_1_4::RS_MobilitySharing
			case 326 : return 1;
			// Tec3_1_5::OC_InTheBuildingAndForGroupsOfOccupants
			case 327 : return 3;
			// Technology::para_weights
			case 328 : return 3;
			// Technology::para_goals
			case 329 : return 3;
			// Utilities::UsageType
			case 330 : return 11;
		} // switch
		throw IBK::Exception(IBK::FormatString("Invalid enumeration type '%1'.")
			.arg(enumtype), "[KeywordList::MaxIndex]");
	}

	const char * KeywordList::Keyword(const char * const enumtype, int t) {
		const char * const kw = theKeyword(enum2index(enumtype), t);
		if (std::string(kw) == INVALID_KEYWORD_INDEX_STRING) {
			throw IBK::Exception(IBK::FormatString("Cannot determine keyword for enumeration type '%1' and index '%2'.")
				.arg(enumtype).arg(t), "[KeywordList::Keyword]");
		}
		return kw;
	}

	bool KeywordList::KeywordExists(const char * const enumtype, const std::string & kw) {
		int typenum = enum2index(enumtype);
		int i = 0;
		int maxIndexInCategory = MaxIndex( enumtype ); 
		for ( ; i <= maxIndexInCategory; ++i ) {
			std::string keywords = allKeywords(typenum, i);
			if (keywords == INVALID_KEYWORD_INDEX_STRING)
				continue;
			std::stringstream strm(keywords);
			int j = 0;
			std::string kws;
			while (strm >> kws) {
				if (kws == kw) {
					return true; // keyword exists
				}
				++j;
			}
		}
		return false; // nothing found keyword doesn't exist.
	}

	int KeywordList::Enumeration(const char * const enumtype, const std::string & kw, bool * deprecated) {
		int typenum = enum2index(enumtype);
		int i = 0;
		int maxIndexInCategory = MaxIndex( enumtype ); 
		for ( ; i <= maxIndexInCategory; ++i ) {
			std::string keywords = allKeywords(typenum, i);
			if (keywords == INVALID_KEYWORD_INDEX_STRING)
				continue;
			std::stringstream strm(keywords);
			int j = 0;
			std::string kws;
			while (strm >> kws) {
				if (kws == kw) {
					if (deprecated != nullptr) {
						*deprecated = (j != 0);
					}
					return i;
				}
				++j;
			}
		} // for ( ; i < maxIndexInCategory; ++i ) {
		throw IBK::Exception(IBK::FormatString("Cannot determine enumeration value for "
			"enumeration type '%1' and keyword '%2'.")
			.arg(enumtype).arg(kw), "[KeywordList::Enumeration]");
	}

	bool KeywordList::CategoryExists(const char * const enumtype) {
		return enum2index(enumtype) != -1;
	}

	void KeywordList::setParameter(IBK::Parameter para[], const char * const enumtype, int n, const double &val) {
		para[n] = IBK::Parameter(Keyword(enumtype, n), val, Unit(enumtype, n));
	}

	void KeywordList::setIntPara(IBK::IntPara para[], const char * const enumtype, int n, const int &val) {
		para[n] = IBK::IntPara(Keyword(enumtype, n), val);
	}

} // namespace DGNB
