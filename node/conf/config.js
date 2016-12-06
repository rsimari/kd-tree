/** configuration for ticket evo **/

const TEvoConf = {
  apiVersion: 9,
  baseUri: "api.sandbox.ticketevolution.com",
  apiKey: process.env.TEVOAPIKEY || "41c8e8f60461b44ab4b00153f0279556",
  secret: process.env.TEVOSECRET || "KpWauBezFWFTS6oBDstWZdLkeYSxmzQ2aG3GeDcP"
}

module.exports = {
  TEvoConf: TEvoConf
}
