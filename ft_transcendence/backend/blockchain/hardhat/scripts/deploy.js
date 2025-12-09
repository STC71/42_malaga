const hre = require("hardhat");
const fs = require('fs');
const path = require('path');

async function main() {
  console.log("🚀 Deploying TournamentRegistry to Avalanche Fuji...");
  console.log("📡 Network:", hre.network.name);
  console.log("⛓️  Chain ID:", hre.network.config.chainId);
  
  const [deployer] = await hre.ethers.getSigners();
  console.log("👤 Deploying with account:", deployer.address);
  
  const balance = await hre.ethers.provider.getBalance(deployer.address);
  console.log("💰 Account balance:", hre.ethers.formatEther(balance), "AVAX");
  
  if (balance === 0n) {
    console.error("❌ ERROR: Account has no AVAX");
    process.exit(1);
  }
  
  console.log("\n📦 Deploying contract...");
  const TournamentRegistry = await hre.ethers.getContractFactory("TournamentRegistry");
  const registry = await TournamentRegistry.deploy();
  
  await registry.waitForDeployment();
  const address = await registry.getAddress();
  
  console.log("\n✅ TournamentRegistry deployed to:", address);
  
  const deployInfo = {
    contractAddress: address,
    network: hre.network.name,
    chainId: hre.network.config.chainId,
    deployedAt: new Date().toISOString(),
    deployer: deployer.address
  };
  
  const outputPath = path.join(__dirname, '..', 'contract-address.json');
  fs.writeFileSync(outputPath, JSON.stringify(deployInfo, null, 2));
  
  console.log("📝 Contract info saved to:", outputPath);
  console.log("\n🔍 View on Snowtrace:");
  console.log(`   https://testnet.snowtrace.io/address/${address}`);
  console.log("\n⏳ Wait ~30 seconds for contract to be indexed...");
  console.log("\n🎉 Deployment completed successfully!");
  console.log("\n💰 Remaining balance:", hre.ethers.formatEther(await hre.ethers.provider.getBalance(deployer.address)), "AVAX");
}

main()
  .then(() => process.exit(0))
  .catch((error) => {
    console.error("\n❌ Deployment failed:");
    console.error(error);
    process.exit(1);
  });
